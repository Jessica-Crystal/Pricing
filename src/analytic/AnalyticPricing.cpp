#include "AnalyticPricing.hpp"

double normalCDF(const double& x) {
   return 0.5 * erfc(-x * M_SQRT1_2);
}

double d_j (const int& j, const double& S, const double& K, const double& r, const double& v,
			const double& T) {
	return (log(S/K) + (r + (pow(-1,j-1))*0.5*v*v)*T)/(v*(pow(T,0.5)));
}

double call_price (const double& S, const double& K, const double& r, const double& v,
				const double& T) {
	return S*normalCDF(d_j(1,S,K,r,v,T)) - K*exp(-r*T)*normalCDF(d_j(2,S,K,r,v,T));
}

double put_price (const double& S, const double& K, const double& r, const double& v,
				const double& T) {
	return -S*normalCDF(-d_j(1,S,K,r,v,T)) + K*exp(-r*T)*normalCDF(-d_j(2,S,K,r,v,T));
}