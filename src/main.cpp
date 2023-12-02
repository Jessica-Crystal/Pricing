#include "MonteCarlo.hpp"
#include "AnalyticPricing.hpp"

int main(){
	static double S = 100.0; // Underlying
	static double K = 100.0; // Strike price
	static double r = 0.05; // Risk-free rate (5%)
	static double v = 0.2; // Volatility of the underlying (20%)
	static double T = 1.0; // One year until expiry
	
	static double S_adjust = S * exp(T*(r-0.5*v*v));
	
	function<void(double,double*)> RandomVector = [](double N, double* X) {
		X[0] = S_adjust * exp(sqrt(v*v*T)*N) - K;
		if (X[0] > 0) {
			X[1] = 0;
		}
		else {
			X[1] = -X[0];
			X[0] = 0;
		}
		return X;
		};
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	MonteCarlo MC(2, RandomVector);
	double* Results = MC.getResults();
	int Nsims;
	double expadj = exp(-r*T);
	double call = call_price(S,K,r,v,T);
	double put = put_price(S,K,r,v,T);
	double MCcall;
	double MCput;
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	cout << "Underlying: " << S << "\n";
	cout << "Strike: " << K << "\n";
	cout << "Risk-Free Rate: " << r << "\n";
	cout << "Volatility: " << v << "\n";
	cout << "Maturity: " << T << "\n\n";
	
	cout << "Analytic pricing -- Call Price: " << call << ",  Put Price: " << put << "\n\n";
	
	cout << "Monte Carlo pricing\n";
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	
	for (int i=0; i<8; i++){
		Nsims = pow(10,i);
		MC.run(Nsims);
		MCcall = Results[0] * expadj;
		MCput = Results[1] * expadj;
		cout << Nsims << " simulations -- Call Price: " << MCcall << ", Error: " 
		<< abs(MCcall-call) << ",  Put Price: " << MCput << ", Error: " 
		<< abs(MCput-put) << "\n";
	}
	

	return 0;
}
