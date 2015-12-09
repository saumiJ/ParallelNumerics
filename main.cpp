#include "test/test.hpp"
#include <mpi/mpi.h>

int rank, size;

int main() {
	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if (rank == 0) {
		std::cout << "Number of processes: " << size << std::endl;
	}

	test_all();

	MPI_Finalize();

	return 1;
}
