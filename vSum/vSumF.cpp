#include "vSum.hpp"

double vSumF(std::vector<double> vec) {
	size_t vecLength = vec.size();
	double result = 0;

	double sum = 0, reducedSum;
	int workSize, gridOffset, currentVecLength, vectorStart;

	currentVecLength = vecLength;
	vectorStart = 0;


	while (currentVecLength > 0) {
		if (currentVecLength > size-1) {
			workSize = currentVecLength / size;
			gridOffset = vectorStart + rank * workSize;

			for (int i = gridOffset; i < gridOffset + workSize; i++) {
				sum += vec[i];
			}

			currentVecLength -= size * workSize;
			vectorStart += size * workSize;
		} else {
			if (rank + 1 <= currentVecLength % size) {
				sum += vec[vectorStart + rank];
			}
			currentVecLength = 0;
		}
	}

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	result = reducedSum;

	return result;
}
