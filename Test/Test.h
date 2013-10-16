#pragma once
//Test:20130920
#include <iostream>

#define FFTK_CHECK_EQUAL(a, b){\
	if(a == b){\
		std::cout << "\033[32m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is succeeded." << "\033[39m" << std::endl;\
	}\
	else{\
		std::cout << "\033[31m" << __FUNCTION__ << "(LINE:" << __LINE__ << ") is failed.\n\t" << #a << " != " << #b \
		<< "\033[39m" << std::endl;\
	}\
}

auto operator==(const std::vector<std::complex<double>>& left, const std::vector<std::complex<double>>& right) -> bool {
	if(left.size() != right.size()){
		return false;	
	}
	for(unsigned int i = 0; i < left.size(); ++i){
		if(abs(left[i] - right[i]) > 1e-10){
			return false;	
		}
	}
	return true;
}

auto Output(std::ostream& os, const std::vector<std::complex<double>>& signal) -> void {
	for(auto& s : signal){
		os << s << " ";
	}
	os << std::endl;
}

auto AbsOutput(std::ostream& os, const std::vector<std::complex<double>>& signal) -> void {
	for(auto& s : signal){
		os << int(abs(s)) << " ";
	}
	os << std::endl;
}
