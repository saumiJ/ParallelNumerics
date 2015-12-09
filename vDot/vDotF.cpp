#include "../vSum/vSum.hpp"
#include "vDot.hpp"

double vDotF(std::vector<double> vec1, std::vector<double> vec2) {
	size_t vec1Length = vec1.size();	// Get sizes of the input vectors
	size_t vec2Length = vec2.size();

	if (vec1Length != vec2Length) {		// If input vectors are not the same length, display error and warn
		std::cout << "vDotF: ERROR! Vector lengths do not match. Result invalid." << std::cout;
		return DBL_MAX;
	}

	double sum = 0,				// Holds partial summation result of this processor
			reducedSum;			// Holds final result of reduction of sum on all processors

	int workSize, 				// Holds the size of the vector to be worked upon by this processor
			gridOffset, 		// Holds the offset from the vector beginning from which this processor should work
			currentVecLength,	// Length of vector left to be worked on
			loopLimit;			// Hold loopLimit to avoid extra addition in loop check

	currentVecLength = vec1Length;			// In the beginning, the whole vector needs to be worked on

	workSize = currentVecLength / size;		// workSize is an integer division of the vector length by #procs
	gridOffset = rank * workSize;			// Offset by the work of previous proc
	loopLimit = gridOffset + workSize;
	for (int i = gridOffset; i < loopLimit; i++) {
		sum += vec1[i] * vec2[i];			// Update local sum
	}

	currentVecLength -= size * workSize;	// Decrease work left

	if (rank + 1 <= currentVecLength % size) {		// If rank falls within indices not worked upon, update local sum again
		sum += vec1[size * workSize + rank] * vec2[size * workSize + rank];
	}
	currentVecLength = 0;

	MPI_Allreduce(&sum, &reducedSum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);	// Combine all sums in reducedSum

	return reducedSum;
}
