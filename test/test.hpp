#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <ctime>
#include <cstdlib>

#include "../vSum/vSum.hpp"
#include "../vDot/vDot.hpp"
#include "../vNorm/vNorm.hpp"

extern int rank, size;

bool test_all();
bool test_vSum();
bool test_vDot();
bool test_vNorm();

#endif /* TEST_HPP */
