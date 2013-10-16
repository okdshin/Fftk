/*
The MIT License (MIT)

Copyright (c) 2013 s.okada

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#ifndef FFTK_H_20131009
#define FFTK_H_20131009
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

#endif
