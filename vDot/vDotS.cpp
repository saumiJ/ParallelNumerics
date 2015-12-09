#include "vDot.hpp"

double vDotS(std::vector<double> vec1, std::vector<double> vec2) {
	if (vec1.size()!= vec2.size()) {	// If input vectors are not the same length, display error and warn
		std::cout << "vDotF: ERROR! Vector lengths do not match. Result invalid." << std::cout;
		return DBL_MAX;
	}

	// Simple dot-product!
	double result = 0;
	for (size_t i = 0; i < vec1.size(); i++) {
		result += vec1[i]*vec2[i];
	}

	return result;
}
