#pragma once
//Utility:20131019
#include <iostream>

namespace fftk
{
auto NearestSquareLength(unsigned int len) -> unsigned int {
	unsigned int res = 1;
	while(len > res){
		res <<= 1;	
	}
	return res;
}
}

