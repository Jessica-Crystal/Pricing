#pragma once
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <functional>

using namespace std;

class MonteCarlo {
public:
	MonteCarlo(int Nscenarios, function<void(double,double*)> RandomVector);
	~MonteCarlo() {
		delete[] CurrVal;
		delete[] Results;
	};
	void sample();
	void run(long unsigned int Nsims);
	void show();
	double* getCurrVal();
	double* getResults();

private:
	int Nscenarios;
	function<void(double,double*)> RandomVector;
	default_random_engine generator;
	normal_distribution<double> N;
	double* CurrVal;
	double* Results;
};