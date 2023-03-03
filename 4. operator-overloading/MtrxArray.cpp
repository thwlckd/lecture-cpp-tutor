#include"MtrxArray.h"
#include<iomanip>

MtrxArray::MtrxArray(int arraySize, int n_row, int n_col)
{
	mtrxArraySize = arraySize;
	pMtrx = new Mtrx[mtrxArraySize];
	for (int i = 0; i < mtrxArraySize; i++)
	{
		pMtrx[i].init(n_row, n_col);  // Mtrx 배열 초기화
	}
}

MtrxArray::~MtrxArray()
{
	/*
	if(pMtrx!=NULL)
		delete [] pMtrx;  // 메모리 반납
	*/
}


Mtrx& MtrxArray::operator[](int sub)
{
	if (isValidIndex(sub) == false)
	{
		cout << "ERROR: Subscript out of range.\n";
		exit(0);
	}
	return pMtrx[sub];
}

bool MtrxArray::isValidIndex(int sub)
{
	if (sub >= 0 && sub < mtrxArraySize)
		return true;
	else
		return false;
}