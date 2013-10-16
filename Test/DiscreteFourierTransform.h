#pragma once
//DiscreteFourierTransform:20131006
#include <iostream>
#include <vector>
#include <cmath>
#include <complex>
#include <iomanip>

namespace fftk{

auto Dft(const std::vector<std::complex<double>>& signal) -> std::vector<std::complex<double>> {
	const auto N = signal.size();
	std::vector<std::complex<double>> res;
	res.reserve(N);
	for(unsigned int i = 0; i < N; ++i){
		std::complex<double> sum(0,0);
		for(unsigned int k = 0; k < N; ++k){
			double t = (-2*M_PI*i*k)/N;	
			sum += signal[k]*exp(std::complex<double>(0, t));
		}
		res.push_back(sum);
	}
	return res;
}

}
