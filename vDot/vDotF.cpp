#include "../vSum/vSum.hpp"
#include "vDot.hpp"

double vDotF(std::vector<double> vec1, std::vector<double> vec2) {
	size_t vec1Length = vec1.size();
	size_t vec2Length = vec2.size();

	if (vec1Length != vec2Length) {
		std::cout << "vDotF: ERROR! Vector lengths do not match. Result invalid." << std::cout;
		return DBL_MAX;
	}

	double sum = 0, reducedSum;

	std::vector<double> dotPart;
	int workSize, gridOffset, currentVecLength, loopLimit;

	currentVecLength = vec1Length;

	workSize = currentVecLength / size;
	gridOffset = rank * workSize;
	loopLimit = gridOffset + workSize;
	for (int i = gridOffset; i < loopLimit; i++) {
		sum += vec1[i] * vec2[i];
	}

	currentVecLength -= size * workSize;

	if (rank + 1 <= currentVecLength % size) {
		sum += vec1[size * workSize + rank] * vec2[size * workSize + rank];
	}
	currentVecLength = 0;

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return reducedSum;
}
