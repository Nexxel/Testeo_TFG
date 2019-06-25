/*
 Calculate the inverse kinematic model of the robot
*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double ar[3];

void multiplyTransformations(double result[4][4], double first[4][4], double second[4][4]);
void mcd(double T05[4][4], double pr[3], double q1, double q2, double q3, double q4, double q5);
void mci(double q[5], double pr[3]);
void updateT05(double T05[4][4], double aux[4][4]);

int main(int argc, char const *argv[])
{
	if(argc == 6){
		double T05[4][4]; double pr[3];
		mcd(T05, pr, atof(argv[1]), atof(argv[2]), atof(argv[3]), atof(argv[4]), atof(argv[5]));
		printf("T05:\n");
		for(int i  = 0; i<4; i++){
			for(int j = 0; j<4; j++){
				printf(" %.4f", T05[i][j]);
			}
			printf("\n");
		}
		printf("Position of the gripper:(%.2f, %.2f, %.2f)\n", pr[0], pr[1], pr[2]);
		//pr[0] = 0.3906171404; pr[1] = -0.0249999047; pr[2] = -0.1200004242;
		//pr[0] = 0.3553365355; pr[1] = 0.0141870280; pr[2] = -0.0904793597;
		pr[0] = 0.3835574148; pr[1] = 0.0134702963; pr[2] = -0.0134702963;
		printf("Position of the gripper:(%.2f, %.2f, %.2f)\n", pr[0], pr[1], pr[2]);

		double q[5];
		mci(q, pr);
		printf("Angles get by the mci: %.2f, %.2f, %.2f, %.2f, %.2f\n", q[0], q[1], q[2], q[3], q[4]);
	}else{
		printf("Not enough arguments: %d provided from 5 needed\n", argc-1);
	}
	return 0;
}


void multiplyTransformations(double result[4][4], double first[4][4], double second[4][4]){
	for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            result[i][j] = 0;
        }
    }
    
    for (int i  = 0; i < 4; i++){
		for (int j = 0;j < 4; j++){
            for (int k = 0; k < 4; k++){
                result[i][j] += (first[i][k] * second[k][j]);
            }
		}
	}
}

/*
Direct kinematic model
	Inputs:
		q1, q2, q3, q4, q5: Angle of each joint

	Outputs:
		T05: Direct kinematic matrix
		pr: Gripper position
*/
void mcd(double T05[4][4], double pr[3], double q1, double q2, double q3, double q4, double q5){
	double L3 = 0.1423;
	double d2 = 0.1528;
	double L45 = 0.1221; //0.07585 + 0.04625;
	double beta = 1.2496;

	double alpha[] = {0, -M_PI/2, M_PI, 0, M_PI/2};
	double a[] = {0,0,d2,L3,0};
	double d[] = {0,0,0,0,0};
	double q[] = {q1,q2-beta,q3-beta,q4+(M_PI/2),q5};

	int i  = 0;
	double T01[][4] = {
		{cos(q[i]), -sin(q[i]), 0, a[i]},
		{sin(q[i])*cos(alpha[i]), cos(q[i])*cos(alpha[i]), -0, -0*d[i]},
		{sin(q[i])*0, cos(q[i])*0, cos(alpha[i]), cos(alpha[i])*d[i]},
		{0, 0, 0, 1}
	};
/*
	printf("T01:\n");
	for(int i  = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			printf(" %.2f", T01[i][j]);
		}
		printf("\n");
	}
*/
	i  = 1;
	double T12[][4] = {
		{cos(q[i]), -sin(q[i]), 0, a[i]},
		{sin(q[i])*0, cos(q[i])*0, -sin(alpha[i]), -sin(alpha[i])*d[i]},
		{sin(q[i])*sin(alpha[i]), cos(q[i])*sin(alpha[i]), 0, 0*d[i]},
		{0, 0, 0, 1}
	};
/*
	printf("T12:\n");
	for(int i  = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			printf(" %.2f", T12[i][j]);
		}
		printf("\n");
	}
*/
	i  = 2;
	double T23[][4] = {
		{cos(q[i]), -sin(q[i]), 0, a[i]},
		{sin(q[i])*cos(alpha[i]), cos(q[i])*cos(alpha[i]), -0, -0*d[i]},
		{sin(q[i])*0, cos(q[i])*0, cos(alpha[i]), cos(alpha[i])*d[i]},
		{0, 0, 0, 1}
	};
/*
	printf("T23:\n");
	for(int i  = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			printf(" %.2f", T23[i][j]);
		}
		printf("\n");
	}
*/
	i  = 3;
	double T34[][4] = {
		{cos(q[i]), -sin(q[i]), 0, a[i]},
		{sin(q[i])*cos(alpha[i]), cos(q[i])*cos(alpha[i]), -0, -0*d[i]},
		{sin(q[i])*0, cos(q[i])*0, cos(alpha[i]), cos(alpha[i])*d[i]},
		{0, 0, 0, 1}
	};
/*
	printf("T34:\n");
	for(int i  = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			printf(" %.2f", T34[i][j]);
		}
		printf("\n");
	}
*/
	i  = 4;
	double T45[][4] = {
		{cos(q[i]), -sin(q[i]), 0, a[i]},
		{sin(q[i])*0, cos(q[i])*0, -sin(alpha[i]), -sin(alpha[i])*d[i]},
		{sin(q[i])*sin(alpha[i]), cos(q[i])*sin(alpha[i]), 0, 0*d[i]},
		{0, 0, 0, 1}
	};
/*
	printf("T45:\n");
	for(int i  = 0; i<4; i++){
		for(int j = 0; j<4; j++){
			printf(" %.2f", T45[i][j]);
		}
		printf("\n");
	}
*/
	double aux[4][4];

	multiplyTransformations(aux, T01, T12);
	
	updateT05(T05, aux);

	multiplyTransformations(aux, T05, T23);

	updateT05(T05, aux);

	multiplyTransformations(aux, T05, T34);

	updateT05(T05, aux);

	multiplyTransformations(aux, T05, T45);

	updateT05(T05, aux);

	double ax = T05[0][2];
	double ay = T05[1][2];
	double az = T05[2][2];
	double px = T05[0][3];
	double py = T05[1][3];
	double pz = T05[2][3];

	pr[0] = px + L45*ax;
	pr[1] = py + L45*ay;
	pr[2] = pz + L45*az;

	ar[0] = ax;
	ar[1] = ay;
	ar[2] = az;
}


/*
Inverse kinematic model
	Inputs:
		pr: Final position of the griper

	Outputs:
		q: Angle of each joint
*/
void mci(double q[5], double pr[3]){

	double L3 = 0.1423;
	double d2 = 0.1528;
	double L45 = 0.1221; //0.07585 + 0.04625;
	double beta = 1.2496;

	int n[3] = {0, 0, 1};
	double px = pr[0] - L45*ar[0];
	double py = pr[1] - L45*ar[1];
	double pz = pr[2] - L45*ar[2];

	printf("px: %.10f, py: %.10f, pz: %.10f", px, py, pz);

	double q1 = atan2(py, px);
	
	double k = pow(pz, 2) + pow(d2, 2) + pow(((px * cos(q1)) + (py * sin(q1))), 2) - pow(L3, 2);
	double k1 = 2 * px * cos(q1) * d2 + 2 * py * sin(q1) * d2;
	double k2 = 2 * pz * d2;

	double theta2b = atan2(k1, k2) - atan2(k, -sqrt(pow(k1,2)+pow(k2,2)-pow(k,2)));
	double q2 = theta2b + beta;

	double theta23 = asin((-pz - d2*sin(theta2b))/L3);
	double q3 = q2 - theta23;

	double L = ar[2]*cos(q2-q3) + ar[0]*sin(q2-q3)*cos(q1) + ar[1]*sin(q2-q3)*sin(q1);
	double q4 = acos(-L) - (M_PI/2);

	double q5 = asin(n[0]*sin(q1) - n[1]*cos(q1));

	printf("\n\nk: %.2f, k1: %.2f, k2: %.2f, theta2b: %.2f, theta23: %.2f, L: %.2f\n", k, k1, k2, theta2b, theta23, L);
    printf("\n\nq1: %.2f\nq2: %.2f\nq3: %.2f\nq4: %.2f\nq5: %.2f\n", q1,q2,q3,q4,q5);

	q[0] = q1;
	q[1] = q2;
	q[2] = q3;
	q[3] = q4;
	q[4] = q5;
}

void updateT05(double T05[4][4], double aux[4][4]){
	for(int i  = 0; i<4; i++){
		for(int j  = 0; j<4; j++){
			T05[i][j] = aux[i][j];
		}
	}
}