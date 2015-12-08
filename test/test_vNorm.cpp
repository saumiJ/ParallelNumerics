#include "test.hpp"

bool test_vNorm() {
	std::vector<double> vec;
	int vecLength = 101231;
	for (int i = 0; i < vecLength; i++) {
		vec.push_back(1.0);
	}

	double normF, normS, timeF, timeS, reducedTimeF, reducedTimeS;
	clock_t begin, end;

	begin = clock();
	normF = vNormF(vec);
	end = clock();
	timeF = double(end - begin) / CLOCKS_PER_SEC;

	if (rank == 0) {
		begin = clock();
		normS = vNormS(vec);
		end = clock();
		timeS = double(end - begin) / CLOCKS_PER_SEC;
	} else {
		timeS = 0;
	}

	MPI_Allreduce(&timeS, &reducedTimeS, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&timeF, &reducedTimeF, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	if (rank == 0) {
		std::cout << "vNormF(vec): " << normF << ", runtime: " << reducedTimeF << std::endl;
		std::cout << "vNormS(vec): " << normS << ", runtime: " << reducedTimeS << std::endl;
	}

	return true;
}
