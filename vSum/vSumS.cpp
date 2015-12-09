#include "vSum.hpp"

double vSumS(std::vector<double> vec) {
	double result = 0;

	// Simple vector-sum!
	for (size_t i = 0; i < vec.size(); i++) {
		result += vec[i];
	}

	return result;
}
