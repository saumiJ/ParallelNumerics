#include "test.hpp"

bool test_all() {

	bool doAllTestsPass = false;

	doAllTestsPass = test_vSum();
	doAllTestsPass = test_vDot();

	return doAllTestsPass;
}
