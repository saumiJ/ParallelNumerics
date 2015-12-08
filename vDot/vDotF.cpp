#include "../vSum/vSum.hpp"
#include "vDot.hpp"

double vDotF(std::vector<double> vec1, std::vector<double> vec2) {
	size_t vec1Length = vec1.size();
	size_t vec2Length = vec2.size();

	if (vec1Length != vec2Length) {
		std::cout << "vDotF: ERROR! Vector lengths do not match. Result invalid." << std::cout;
		return DBL_MAX;
	}

	double sum, reducedSum;

	std::vector<double> dotPart;
	int workSize, gridOffset, currentVecLength, vectorStart;

	currentVecLength = vec1Length;
	vectorStart = 0;

	while (currentVecLength > 0) {
		if (currentVecLength > size-1) {
			workSize = currentVecLength / size;
			gridOffset = vectorStart + rank * workSize;

			for (int i = gridOffset; i < gridOffset + workSize; i++) {
				sum += vec1[i] * vec2[i];
			}

			currentVecLength -= size * workSize;
			vectorStart += size * workSize;
		} else {
			if (rank + 1 <= currentVecLength % size) {
				sum += vec1[vectorStart + rank] * vec2[vectorStart + rank];
			}
			currentVecLength = 0;
		}
	}

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	return reducedSum;
}
