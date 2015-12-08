#include "../vSum/vSum.hpp"
#include "vDot.hpp"

double vDotF(std::vector<double> vec1, std::vector<double> vec2) {
	size_t vec1Length = vec1.size();
	size_t vec2Length = vec2.size();

	if (vec1Length != vec2Length) {
		std::cout << "vDotF: ERROR! Vector lengths do not match. Result invalid." << std::cout;
		return DBL_MAX;
	}

	double result;

	std::vector<double> dotPart;
	size_t workSize, gridOffset, currentVecLength, vectorStart;

	currentVecLength = vec1Length;
	vectorStart = 0;

	while (currentVecLength > 0) {
		if (currentVecLength > size-1) {
			workSize = currentVecLength / size;
			gridOffset = vectorStart + rank * workSize;

			for (size_t i = gridOffset; i < gridOffset + workSize; i++) {
				dotPart.push_back(vec1[i]*vec2[i]);
			}

			currentVecLength -= size * workSize;
			vectorStart += size * workSize;
		} else {
			if (rank + 1 <= currentVecLength % size) {
				dotPart.push_back(vec1[vectorStart + rank]*vec2[vectorStart + rank]);
			}
			currentVecLength = 0;
		}
	}

	std::vector<double> dotFull;
	dotFull.reserve(vec1Length);

	if (rank == 0) {
		dotFull.insert(dotFull.end(), dotPart.begin(), dotPart.end());
		std::vector<double> scoop;
		size_t receiveSize = 0;
		for (int i = 1; i < size; i++) {
			MPI_Recv(&receiveSize, 1, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			scoop.resize(receiveSize);
			MPI_Recv(&scoop[0], receiveSize, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			dotFull.insert(dotFull.end(), scoop.begin(), scoop.end());
		}
	} else {
		size_t sendSize = dotPart.size();
		MPI_Send(&sendSize, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&dotPart[0], sendSize, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
		dotFull.resize(vec1Length);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Bcast(&dotFull[0], vec1Length, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	result = vSumF(dotFull);

	return result;
}
