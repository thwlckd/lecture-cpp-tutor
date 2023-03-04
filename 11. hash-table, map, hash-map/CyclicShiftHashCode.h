#pragma once

#ifndef CYCLIC_SHIFT_HASH_CODE_H
#define CYCLIC_SHIFT_HASH_CODE_H

#include <string>

using namespace std;

#define BIT_SHIFTS 5  // 5 일때 가장 효율적인 hash table 구성
#define BITS_INT 32

class CyclicShiftHashCode 
{
public:
	int operator() (const string key)  // operator overloading of () 
	{ 
		int len = key.length(); 
		unsigned int h = 0; 

		for (int i = 0; i<len; i++) 
		{ 
			h = (h << BIT_SHIFTS) | (h >> (BITS_INT - BIT_SHIFTS));
			h += (unsigned int)key.at(i); 
		}
		return h;
	} 
};

#endif
