#include "vSum.hpp"

double vSumF(std::vector<double> vec) {
	size_t vecLength = vec.size();

	double sum = 0, reducedSum;
	int workSize, gridOffset, currentVecLength;

	currentVecLength = vecLength;
	int loopLimit;

	workSize = currentVecLength / size;
	gridOffset = rank * workSize;
	loopLimit = gridOffset + workSize;
	for (int i = gridOffset; i < loopLimit; i++) {
		sum += vec[i];
	}

	currentVecLength -= size * workSize;

	if (rank + 1 <= currentVecLength % size) {
		sum += vec[size * workSize + rank];
	}

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return reducedSum;
}
