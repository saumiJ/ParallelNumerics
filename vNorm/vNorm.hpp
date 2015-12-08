#ifndef VNORM_HPP
#define VNORM_HPP

#include <vector>
#include <iostream>
#include <cmath>
#include <mpi/mpi.h>

extern int rank, size;

double vNormF(std::vector<double> vec);
double vNormS(std::vector<double> vec);

#endif /* VNORM_HPP */
