#ifndef VNORM_HPP
#define VNORM_HPP

/*
 * Header for vector-2-norm implementations. Add implementation for vector-2-norm here.
 * TODO: Implement proper fan-in for O(log(n))
 * TODO: Template calls
 */

#include <vector>
#include <iostream>
#include <cmath>
#include <mpi/mpi.h>

extern int rank, size;	// rank and size global to whole project

double vNormF(std::vector<double> vec);		// Parallel vector-2-norm
double vNormS(std::vector<double> vec);		// Serial vector-2-norm

#endif /* VNORM_HPP */
