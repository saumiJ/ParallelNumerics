#ifndef TEST_HPP
#define TEST_HPP

/*
 * Header for tests. Add tests here for new functions.
 */

#include <vector>
#include <ctime>
#include <cstdlib>

#include "../vSum/vSum.hpp"
#include "../vDot/vDot.hpp"
#include "../vNorm/vNorm.hpp"

extern int rank, size;

bool test_all();	// Calls all tests
bool test_vSum();	// Test vSum functions
bool test_vDot();	// Test vDot functions
bool test_vNorm();	// Test vNorm functions

#endif /* TEST_HPP */
