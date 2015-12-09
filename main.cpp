#include "test/test.hpp"
#include <mpi/mpi.h>

int rank, size;		// Global external variables

int main(int argc, char** argv) {
	MPI_Init(&argc, &argv);			// Initialize MPI environment

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);	// Get rank (procID)
	MPI_Comm_size(MPI_COMM_WORLD, &size);	// Get size (#procs)

	if (rank == 0) {
		std::cout << "Number of processes: " << size << std::endl;
	}

	bool wereTestsSuccessful = test_all();	// Check if tests pass

	if (rank == 0) {
		if(wereTestsSuccessful) {
			std::cout << "Tests successful!" << std::endl;
		} else {
			std::cout << "Tests failed!" << std::endl;
		}
	}

	MPI_Finalize();		// Conclude MPI

	return 0;
}
