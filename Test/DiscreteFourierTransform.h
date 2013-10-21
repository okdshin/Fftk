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

class DiscreteFourierTransform{
public:
	auto Transform(const std::vector<std::complex<double>>& signal) -> std::vector<std::complex<double>> {
		return DoTransform(signal, false);
	}

	auto InverseTransform(const std::vector<std::complex<double>>& signal) -> std::vector<std::complex<double>> {
		auto res = DoTransform(signal, true);
		for(auto& e : res){
			e /= static_cast<double>(signal.size());
		}
		return res;
	}

private:
	auto DoTransform(const std::vector<std::complex<double>>& signal, bool is_inv) -> std::vector<std::complex<double>> {
		const auto N = signal.size();
		std::vector<std::complex<double>> res;
		res.reserve(N);
		for(unsigned int i = 0; i < N; ++i){
			std::complex<double> sum(0,0);
			for(unsigned int k = 0; k < N; ++k){
				double t = is_inv ? 2*M_PI*i*k/N : (-2*M_PI*i*k)/N;	
				sum += signal[k]*exp(std::complex<double>(0, t));
			}
			res.push_back(sum);
		}
		return res;
	}
};

}
