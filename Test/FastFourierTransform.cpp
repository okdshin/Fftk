#ifdef FASTFOURIERTRANSFORM_UNIT_TEST
#include "../FastFourierTransform.h"
#include <iostream>
#include "DiscreteFourierTransform.h"
#include "Test.h"

using namespace fftk;

auto CheckFft() -> void {
	std::vector<std::complex<double>> source_signal;

	for(double i = 0; i < 2*M_PI; i+=(2*M_PI/512.0)){
		source_signal.push_back(std::complex<double>(cos(i)+cos(i*10), 0));
	}
	std::complex<double> sum = 0.0;
	for(auto source : source_signal){
		sum += source;	
	}
	std::cout << "signal_sum: " << sum << std::endl;
	
	Output(std::cout << "src: ", source_signal);
	
	FastFourierTransform fft(SignalLength(512));
	auto fft_dest_signal = fft.Transform(source_signal);
	AbsOutput(std::cout << "fft: ", fft_dest_signal);
	
	auto dft_dest_signal = Dft(source_signal);
	AbsOutput(std::cout << "dft: ", dft_dest_signal);

	FFTK_CHECK_EQUAL(dft_dest_signal, fft_dest_signal);	
	
	auto fft_inv_dest_signal = fft.InverseTransform(fft_dest_signal);
	Output(std::cout << "inv_fft: ", fft_inv_dest_signal);
	FFTK_CHECK_EQUAL(source_signal, fft_inv_dest_signal);	
}

int main(int argc, char* argv[])
{
	CheckFft();
    return 0;
}

#endif
