#ifndef TEST_HPP
#define TEST_HPP

#include <vector>
#include <ctime>
#include <cstdlib>

#include "../vSum/vSum.hpp"
#include "../vDot/vDot.hpp"

extern int rank, size;

bool test_all();
bool test_vSum();
bool test_vDot();

#endif /* TEST_HPP */
