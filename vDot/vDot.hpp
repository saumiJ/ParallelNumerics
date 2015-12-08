#ifndef VDOT_HPP
#define VDOT_HPP

#include <iostream>
#include <vector>
#include <cfloat>
#include <mpi/mpi.h>

extern int rank, size;

double vDotF(std::vector<double> vec1, std::vector<double> vec2);
double vDotS(std::vector<double> vec1, std::vector<double> vec2);

#endif /* VDOT_HPP */
