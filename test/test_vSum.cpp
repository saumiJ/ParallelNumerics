#include "test.hpp"

bool test_vSum() {
	std::vector<double> vec;
	size_t vecLength = 5000000;
	for (size_t i = 0; i < vecLength; i++) {
		vec.push_back(1.0);
	}

	double sumF, sumS, timeF, timeS, reducedTimeF, reducedTimeS;
	clock_t begin, end;

	begin = clock();
	sumF = vSumF(vec);
	end = clock();
	timeF = double(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	sumS = vSumS(vec);
	end = clock();
	timeS = double(end - begin) / CLOCKS_PER_SEC;

	MPI_Allreduce(&timeS, &reducedTimeS, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&timeF, &reducedTimeF, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	if (rank == 0) {
		std::cout << "vSumF(vec): " << sumF << ", runtime: " << reducedTimeF << std::endl;
		std::cout << "vSumS(vec): " << sumS << ", runtime: " << reducedTimeS << std::endl;
	}

	return true;
}
