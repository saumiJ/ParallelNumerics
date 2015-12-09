#include "test.hpp"

bool test_vNorm() {
	std::vector<double> vec;				// Create two test vectors
	int vecLength = 20000000;				// Assign length (not bigger than 2e7 on Saumi's machine)
	for (int i = 0; i < vecLength; i++) {	// Initialize
		vec.push_back(1.0);
	}

	double normF,			// Holds result of vDotF
			timeF,			// Holds cumulative runtime of vDotF
			normS,			// Holds result of vDotS
			timeS,			// Holds serial runtime of vDotS
			reducedTimeS;	// Holds summation of timeS from all processes

	clock_t begin_F,		// Holds earliest begin cycle for vDotF
			end_F,			// Holds latest end cycle for vDotF
			begin_S,		// Holds begin cycle for vDotS
			end_S;			// Holds end cycle for vDotS

	begin_F = clock();			// Store time
	normF = vNormF(vec);		// Call vNormF on vec
	end_F = clock();			// Store time

	begin_S = clock();									// Store cycle
	normS = vNormS(vec);							// Call vNormS on vec
	end_S = clock();									// Store cycle
	timeS = double(end_S - begin_S) / CLOCKS_PER_SEC;	// Compute runtime

	if (normF != normS) {		// Return false for unequal serial and parallel results
		return false;
	}

	MPI_Allreduce(&timeS, &reducedTimeS, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);	// Sum up serial runtime of all processes

	if (rank == 0) {								// If master process
		for (int i = 1; i < size; i++) {			// get begin_F and end_F from other processes
			clock_t clockScoop;
			MPI_Recv(&clockScoop, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (clockScoop < begin_F) {				// If current begin_F came later than the one received
				begin_F = clockScoop;				// replace begin_F with received
			}
			MPI_Recv(&clockScoop, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (clockScoop > end_F) {				// If current end_F came earlier than the one received
				end_F = clockScoop;					// replace end_F with received
			}
		}
															// Once we have the earliest begin_F and latest end_F
		timeF = double(end_F - begin_F) / CLOCKS_PER_SEC;	// Compute parallel runtime
	} else {												// If slave, send begin_F and end_F
		MPI_Send(&begin_F, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
		MPI_Send(&end_F, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	}

	if (rank == 0) {								// If master, display runtimes and results
		std::cout << "vNormF(vec): " << normF << ", runtime: " << timeF << std::endl;
		std::cout << "vNormS(vec): " << normS << ", runtime: " << reducedTimeS/size << std::endl;
	}

	return true;
}
