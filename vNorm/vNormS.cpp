#include "vNorm.hpp"

double vNormS(std::vector<double> vec) {
	double result = 0, vecLength = vec.size();

	// Simple vector-2-norm!
	for (size_t i = 0; i < vecLength; i++) {
		result += vec[i] * vec[i];
	}
	result = sqrt(result);
	return result;
}
