#ifndef VSUM_HPP
#define VSUM_HPP

#include <iostream>
#include <vector>
#include <mpi/mpi.h>

/*
 * Header for vector-sum implementations. Add implementation for vector-sum here.
 * TODO: Implement proper fan-in for O(log(n))
 * TODO: Template calls
 */

extern int rank, size;	// rank and size global to whole project

double vSumF(std::vector<double> vec);	// Parallel vector-sum
double vSumS(std::vector<double> vec);	// Serial vector-sum

#endif /* VSUM_HPP */
