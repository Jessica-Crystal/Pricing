#include <cmath>

double normalCDF(const double& x);

double d_j (const int& j, const double& S, const double& K, const double& r, const double& v,
			const double& T);

double call_price (const double& S, const double& K, const double& r, const double& v,
                const double& T);

double put_price (const double& S, const double& K, const double& r, const double& v,
				const double& T);