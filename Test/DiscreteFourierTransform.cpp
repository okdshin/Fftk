#ifdef DISCRETEFOURIERTRANSFORM_UNIT_TEST
#include "DiscreteFourierTransform.h"
#include <iostream>
#include "Test.h"

using namespace fftk;

int main(int argc, char* argv[])
{
	unsigned int signal_len = 8;
	std::vector<std::complex<double>> source_signal;
	for(double i = 0; i < 2*M_PI; i+=(2*M_PI/static_cast<double>(signal_len))){
		source_signal.push_back(std::complex<double>(cos(i)+cos(i*10), 0));
	}
	DiscreteFourierTransform dft;
	auto dest_signal = dft.Transform(source_signal);
	Output(std::cout << "transform: ", dest_signal);
	Output(std::cout << "inverse: ", dft.InverseTransform(dest_signal));
	Output(std::cout << "source: ", source_signal);

	FFTK_CHECK_EQUAL(dest_signal, dest_signal);

    return 0;
}

#endif
