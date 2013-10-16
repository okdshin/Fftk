#ifdef TEST_UNIT_TEST
#include "Test.h"
#include <iostream>

auto CorrectTestFunc() -> void {
	FFTK_CHECK_EQUAL(1, 1);	
}

auto IncorrectTestFunc() -> void {
	FFTK_CHECK_EQUAL(1, 2);	
}

int main(int argc, char* argv[])
{
	CorrectTestFunc();
	IncorrectTestFunc();
    return 0;
}

#endif
