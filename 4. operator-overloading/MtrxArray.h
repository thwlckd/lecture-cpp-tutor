#pragma once

#ifndef MTRXARRAY_H
#define MTRXARRAY_H

#include <iostream>
#include "Mtrx.h"

using namespace std;

class Mtrx;
class MtrxArray
{
public:
    MtrxArray(int arraySize, int n_row, int n_col); // constructor
    ~MtrxArray(); // destructor
    Mtrx& operator[](int);
    int getSize() { return mtrxArraySize; }
private:
    Mtrx* pMtrx;
    int mtrxArraySize;
    bool isValidIndex(int index);
};
#endif