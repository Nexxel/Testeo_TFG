#include <stdio.h>
#define ARMA_DONT_USE_WRAPPER
#include <armadillo>
#include <eigen3/Eigen/Dense>
#include <gsl/gsl_linalg.h>

using namespace std;
using namespace arma;
using namespace Eigen;

int main(int argc, char const *argv[])
{
    // ARMADILLO
    mat P; mat P2I; mat I2P;
    
    P << 554.25 << 0 << 320.5 << 0 << endr 
      << 0 << 554.25 << 240.5 << 0 << endr
      << 0 << 0 << 1 << 1 << endr;

    P2I << 1 << 0 << 320.5 << endr
        << 0 << -1 << 240.5 << endr
        << 0 << 0 << 1 << endr;
    
    I2P = inv(P2I);

    vec initial;

    initial << 0 << 0 << 0 << 1;

    vec test = P2I * P * initial;
     /*
     vec test;
     test << 320.5 << 240.5 << 1;
     */
    // vec x = solve(P, I2P * zero);
    //vec x = pinv(P, 0.0, "std") * I2P * zero;
    vec e = I2P * test;
    double x4 = 1;
    double x3 = e(2) - P(2,3);
    double x2 = (e(1) - P(1,2)*e(2) + P(2,3)*P(1,2))/P(1,1);
    double x1 = (e(0) - P(0,2)*e(2) + P(2,3)*P(0,2))/P(0,0);

    vec x;

    x << x1 << x2 << x3 << x4;

    vec4 pepe;
    pepe << 1 << 2 << 3 << 4;
    pepe /= pepe(3);
    vec3 paco = pepe.rows(0,2);

    cout << paco << endl;

    cout << "\n===============ARMADILLO================\n" 
         << "x: \n" << x
         << "\n===============================\n" 
         << endl;
/* 
    // EIGEN
    MatrixXf P_eig(3,4);
    P_eig << 554.25, 0.0, 320.5, 0.0, 
             0.0, 554.25, 240.5, 0.0,
             0.0, 0.0, 1.0, 1.0;

    Matrix3f I2P_eig;
    I2P_eig << 1.0, 0.0, -320.5,
               0.0, -1.0, 240.5,
               0.0, 0.0, 1.0;
    
    Vector3f zero_eig;
    zero_eig << 320.5, 240.5, 1.0;
    
    Vector4f x_eig = P_eig.colPivHouseholderQr().solve(I2P_eig * zero_eig);

     cout << "\n===============EIGEN================\n" 
          << "x_eig: \n" << x_eig
          << "\n===============================\n" 
          << endl;

     // GSL
     double P_data[] = {554.25, 0.0, 320.5, 0.0, 
                       0.0, 554.25, 240.5, 0.0,
                       0.0, 0.0, 1.0, 1.0};
     double I2P_data[] = {1.0, 0.0, -320.5,
                         0.0, -1.0, 240.5,
                         0.0, 0.0, 1.0};
     double zero_data[] = {320.5, 240.5, 1};
     double zero_P[] = {240.5, 0, 1};

     gsl_matrix_view P_gsl = gsl_matrix_view_array(P_data, 3, 4);
     gsl_matrix_view I2P_gsl = gsl_matrix_view_array(I2P_data, 3, 3);
     gsl_vector_view zero_gsl = gsl_vector_view_array(zero_P, 3);

     gsl_vector *x_gsl = gsl_vector_alloc(4);
     gsl_vector *residual = gsl_vector_alloc(3);
     gsl_vector *tau = gsl_vector_alloc(3);
     gsl_matrix *Q = gsl_matrix_alloc(3, 3);
     gsl_matrix *R = gsl_matrix_alloc(3,4);
     gsl_linalg_QR_decomp(&P_gsl.matrix, tau);
     gsl_linalg_QR_unpack(&P_gsl.matrix, tau, Q, R);
     gsl_linalg_QR_QRsolve(Q, R, &zero_gsl.vector, x_gsl);
     //gsl_linalg_QR_solve(&P_gsl.matrix, tau, &zero_gsl.vector, x_gsl);
     cout << "\n===============GSL================\n" 
          << "x_gsl: \n";
          gsl_vector_fprintf(stdout, x_gsl, "%g");
          cout << "\n===============================\n" 
          << endl;
     gsl_vector_free (x_gsl);
     gsl_vector_free (tau);
     gsl_vector_free (residual);
     */
    return 0;
}

