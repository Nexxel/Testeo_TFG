/*
Sergio Gonzalez Muriel
Degree thesis:  Reinforcement learning for object manipulation by a robotic arm
Test code for checking the version of the aramdillo library
*/

#include <iostream>
#include <armadillo>

int main(){
	arma::arma_version ver;
	std::cout << "ARMA version: "<< ver.as_string() << std::endl;
}