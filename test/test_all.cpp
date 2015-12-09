#include "test.hpp"

bool test_all() {

	bool doAllTestsPass = false;	// Pass/fail flag

	doAllTestsPass = test_vSum();	// Test vSum
	doAllTestsPass = test_vDot();	// Test vDot
	doAllTestsPass = test_vNorm();	// Test vNorm

	return doAllTestsPass;
}
