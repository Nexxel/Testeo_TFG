/*
Sergio Gonzalez Muriel
Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
Test code for showing matrices correctly in C++03
*/

#include <stdio.h>

using namespace std;


int main()
{
    int a = 20; 
    int array_de_cuatro[][4] = {{1,a,3,4},{a,6,7,8}};
    for(int i = 0; i<2; i++){
        for(int j = 0; j<4; j++){
            printf("%u\n", array_de_cuatro[i][j]);
        }
    }
    return 0;
}
