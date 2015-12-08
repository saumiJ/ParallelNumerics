#include "../vSum/vSum.hpp"
#include "vNorm.hpp"

double vNormF(std::vector<double> vec) {
	size_t vecLength = vec.size();

	double result;

	std::vector<double> dotPart;
	int workSize, gridOffset, currentVecLength, vectorStart;

	currentVecLength = vecLength;
	vectorStart = 0;

	while (currentVecLength > 0) {
		if (currentVecLength > size-1) {
			workSize = currentVecLength / size;
			gridOffset = vectorStart + rank * workSize;

			for (int i = gridOffset; i < gridOffset + workSize; i++) {
				dotPart.push_back(vec[i]*vec[i]);
			}

			currentVecLength -= size * workSize;
			vectorStart += size * workSize;
		} else {
			if (rank + 1 <= currentVecLength % size) {
				dotPart.push_back(vec[vectorStart + rank]*vec[vectorStart + rank]);
			}
			currentVecLength = 0;
		}
	}

	std::vector<double> dotFull;
	dotFull.reserve(vecLength);

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
		dotFull.resize(vecLength);
	}

	MPI_Barrier(MPI_COMM_WORLD);

	MPI_Bcast(&dotFull[0], vecLength, MPI_DOUBLE, 0, MPI_COMM_WORLD);

	result = vSumF(dotFull);

	result = sqrt(result);

	return result;
}
