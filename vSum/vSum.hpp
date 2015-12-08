#ifndef VSUM_HPP
#define VSUM_HPP

#include <iostream>
#include <vector>
#include <mpi/mpi.h>

extern int rank, size;

double vSumF(std::vector<double> vec);
double vSumS(std::vector<double> vec);

#endif /* VSUM_HPP */
