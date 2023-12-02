#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(int Nscenarios, function<void(double,double*)> RandomVector)
	: generator(time(0)) {
		
	this->Nscenarios = Nscenarios;
	this->RandomVector = RandomVector;
	CurrVal = new double[Nscenarios];
	Results = new double[Nscenarios];
}
//~~~~~~~~~~~~~~~~~~~~sample()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::sample() {
	
	RandomVector(N(generator),CurrVal);
}
//~~~~~~~~~~~~~~~~~~~run()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::run(long unsigned int Nsims) {
	
	for (int i=0; i<Nscenarios; i++) {
		Results[i] = 0;
	}
	for (long unsigned int k=0; k<Nsims; k++) {
		sample();
		for (int i=0; i<Nscenarios; i++) {
			Results[i] += CurrVal[i];
		}
	}
	for (int i=0; i<Nscenarios; i++) {
		Results[i] /= Nsims;
	}
}
//~~~~~~~~~~~~~~~~~~~show()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::show() {
	
	for (int i=0; i<Nscenarios; i++) {
		cout << "Scenario " << i+1 << ": " << Results[i] << "\n";
	}
}
	
double* MonteCarlo::getCurrVal() {
	return CurrVal;
}
	
double* MonteCarlo::getResults() {
	return Results;
}