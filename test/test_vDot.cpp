#include "test.hpp"

bool test_vDot() {
	std::vector<double> vec1;
	std::vector<double> vec2;
	int vecLength = 100000000;
	for (int i = 0; i < vecLength; i++) {
		vec1.push_back(1.0);
		vec2.push_back(2.0);
	}

	double dotF, timeF, dotS, timeS, reducedTimeF, reducedTimeS;
	clock_t begin, end;

	begin = clock();
	dotF = vDotF(vec1, vec2);
	end = clock();
	timeF = double(end - begin) / CLOCKS_PER_SEC;

	begin = clock();
	dotS = vDotS(vec1, vec2);
	end = clock();
	timeS = double(end - begin) / CLOCKS_PER_SEC;

	MPI_Allreduce(&timeS, &reducedTimeS, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
	MPI_Allreduce(&timeF, &reducedTimeF, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

	if (rank == 0) {
		std::cout << "vDotF(vec1, vec2): " << dotF << ", runtime: " << reducedTimeF << std::endl;
		std::cout << "vDotS(vec1, vec2): " << dotS << ", runtime: " << reducedTimeS << std::endl;
	}

	return true;
}
