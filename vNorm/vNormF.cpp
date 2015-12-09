#include "../vSum/vSum.hpp"
#include "vNorm.hpp"

double vNormF(std::vector<double> vec) {
	size_t vecLength = vec.size();		// Get size of the input vector

	double sum = 0,				// Holds partial summation result of this processor
			reducedSum;			// Holds final result of reduction of sum on all processors

	int workSize, 				// Holds the size of the vector to be worked upon by this processor
			gridOffset, 		// Holds the offset from the vector beginning from which this processor should work
			currentVecLength,	// Length of vector left to be worked on
			loopLimit;			// Hold loopLimit to avoid extra addition in loop check

	currentVecLength = vecLength;			// In the beginning, the whole vector needs to be worked on

	workSize = currentVecLength / size;		// workSize is an integer division of the vector length by #procs
	gridOffset = rank * workSize;			// Offset by the work of previous proc
	loopLimit = gridOffset + workSize;
	for (int i = gridOffset; i < loopLimit; i++) {
		sum += vec[i] * vec[i];			// Update local sum
	}

	currentVecLength -= size * workSize;	// Decrease work left

	if (rank + 1 <= currentVecLength % size) {		// If rank falls within indices not worked upon, update local sum again
		sum += vec[size * workSize + rank] * vec[size * workSize + rank];
	}

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);	// Combine all sums in reducedSum

	return sqrt(reducedSum);
}
