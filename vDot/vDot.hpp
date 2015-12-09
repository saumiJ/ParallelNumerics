#ifndef VDOT_HPP
#define VDOT_HPP

/*
 * Header for dot-product implementations. Add implementation for dot-product here.
 * TODO: Implement proper fan-in for O(log(n))
 * TODO: Template calls
 */

#include <iostream>
#include <vector>
#include <cfloat>
#include <mpi/mpi.h>

extern int rank, size;	// rank and size global to whole project

double vDotF(std::vector<double> vec1, std::vector<double> vec2);	// Parallel dot-product
double vDotS(std::vector<double> vec1, std::vector<double> vec2);	// Serial dot-product

#endif /* VDOT_HPP */
