#ifdef DISCRETEFOURIERTRANSFORM_UNIT_TEST
#include "DiscreteFourierTransform.h"
#include <iostream>
#include "Test.h"

using namespace fftk;

int main(int argc, char* argv[])
{
	std::vector<std::complex<double>> source_signal;
	for(unsigned int i = 0; i < 16; ++i){
		source_signal.push_back(std::complex<double>(i, 0));
	}
	Output(std::cout, source_signal);
	auto dest_signal = Dft(source_signal);
	Output(std::cout, dest_signal);

	FFTK_CHECK_EQUAL(dest_signal, dest_signal);

    return 0;
}

#endif
