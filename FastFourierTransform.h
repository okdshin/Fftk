#pragma once
//FastFourierTransform:20131009
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <complex>

namespace fftk {

class SignalLengthBitSize {
public:
	SignalLengthBitSize(unsigned int size) : size_(size){}
	auto operator()()const -> unsigned int {
		return size_;	
	}

private:
	unsigned int size_;
};

class SignalLength {
public:
	SignalLength(unsigned int size) : size_(size){}
	auto operator()()const -> unsigned int {
		return size_;	
	}
private:
	unsigned int size_;
};

class FastFourierTransform{
public:
    explicit FastFourierTransform(const SignalLength& signal_length) : 
			n_level_(0), n_(signal_length()), index_list_(1, 0){
		auto n = n_;
		while(n != 1){
			assert((n&1) != 1);
			++n_level_;
			n >>= 1;
		}
		InitMemos();
	}
    explicit FastFourierTransform(const SignalLengthBitSize& bit_size) : 
			n_level_(bit_size()), n_(1), index_list_(1, 0){
		assert(n_level_ < 64);
		n_ <<= n_level_;
		InitMemos();
	}
    ~FastFourierTransform(){}

	auto operator()(const std::vector<std::complex<double>>& signal) -> std::vector<std::complex<double>> {
		assert(signal.size() == n_);
		
		std::vector<std::complex<double>> src;
		src.reserve(signal.size());
		for(const auto index : index_list_){
			src.push_back(signal[index]);
		}
		std::vector<std::complex<double>> res;
		for(unsigned int i = 0; i < n_level_; ++i){
			res = std::vector<std::complex<double>>(n_, std::complex<double>(0, 0));
			unsigned int block_num = static_cast<unsigned int>(1 << (n_level_-static_cast<int>(i)-1));
			for(unsigned int j = 0; j < block_num; ++j){
				unsigned int wing = 1 << i;
				for(unsigned int k = 0; k < wing; ++k){
					unsigned int index = k + 2*wing*j;
					res[index] += src[index];
					res[index+wing] += src[index];	
					
					auto w = w_table_[i][k];
					auto t = w*src[index+wing];
					res[index] += t;
					res[index+wing] += -t;
				}
			}
			src = res;
		}
		return res;
		
	}
private:
	auto InitMemos() -> void {
		InitIndexList();
		InitWtable();
	}

	auto InitIndexList() -> void {
		index_list_.reserve(n_);
		for(unsigned int i = 0; i < n_level_; ++i){
			index_list_.insert(index_list_.end(), index_list_.begin(), index_list_.end());
			for(unsigned int j = 0; j < index_list_.size(); ++j){
				index_list_[j] *= 2;
			}
			for(unsigned int j = index_list_.size()/2; j < index_list_.size(); ++j){
				index_list_[j] += 1;
			}
		}
	}

	auto InitWtable() -> void {
		w_table_.clear();
		for(unsigned int i = 0; i < n_level_; ++i){
			unsigned int wing = 1 << i;
			std::vector<std::complex<double>> w_table_row(wing, std::complex<double>(0.0, 0.0));
			for(unsigned int k = 0; k < wing; ++k){
				w_table_row[k] = CalcW(k, 2 << i);
			}
			w_table_.push_back(w_table_row);
		}
	}

	auto CalcW(unsigned int k, unsigned int n)const -> std::complex<double> {
		return exp(std::complex<double>(0, (-2*M_PI*k)/n));
	}

	unsigned int n_level_;
	unsigned int n_;
	std::vector<unsigned int> index_list_;
	std::vector<std::vector<std::complex<double>>> w_table_;
};

}

