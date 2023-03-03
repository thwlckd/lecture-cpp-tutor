#include "Class_Mtrx.h"
#include <iostream>
#include <iomanip>

using namespace std;

typedef double* DBLPTR;

Mtrx::Mtrx(int num_row, int num_col)
{
	int i, j;
	n_row = num_row;
	n_col = num_col;
	dM = new DBLPTR[n_row];  // 행의 크기만큼 1차원 배열 동적 할당

	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];  // 열의 크기만큼 2차원 배열 동적 할당
	}
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			dM[i][j] = 0.0;  // 생성 배열 초기화
		}
	}
}

Mtrx::~Mtrx()
{
	/* 동적 메모리 반납
	for (int i=0; i<n_row; i++)
	delete [] dM[i];
	delete [] dM;
	*/
}

Mtrx::Mtrx(istream& fin)
{
	int i, j, size_row, size_col, num_data, cnt;
	double d;
	fin >> size_row >> size_col;  // 파일로부터 행/렬의 크기 받아옴
	n_row = size_row;
	n_col = size_col;
	dM = new DBLPTR[n_row];  // 받아온 행의 크기로 1차원 배열 동적 생성
	for (i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];  // 받다온 열의 크기로 2차원 배열 동적 생성
	}
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			if (fin.eof())
				dM[i][j] = 0.0;
			else
			{
				fin >> d;  // 파일로부터 정수 받아와
				dM[i][j] = d;  // 2차원 배열에 할당
			}
		}
	}
}

#define SETW 6
void Mtrx::fprintMtrx(ostream& fout)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2, a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;  // 확장 완성형 코드 사용하기 위한 변수 선언
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(2);
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(SETW) << dM[i][j];  // 0xa6, 0xa3: ┌
			else if ((i == 0) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a4;  // 0xa6, 0xa4:  ┐
			else if ((i > 0) && (i < (n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(SETW) << dM[i][j];  // 0xa6, 0xa2: │(table 좌측에 출력) 
			else if ((i > 0) && (i < (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a2;  // 0xa6, 0xa2: │(table 우측에 출력)
			else if ((i == (n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(SETW) << dM[i][j];  // 0xa6, 0xa6: └
			else if ((i == (n_row - 1)) && (j == (n_col - 1)))
				fout << setw(SETW) << dM[i][j] << a6 << a5;  // 0xa6, 0xa5:  ┘
			else
				fout << setw(SETW) << dM[i][j];
		}
		fout << endl;
	}
	fout << endl;
}

const Mtrx Mtrx::add(const Mtrx& mA)
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName('R');
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
		}
	}
	return mR;
}

const Mtrx Mtrx::sub(const Mtrx& mA)
{
	int i, j;
	Mtrx mR(n_row, n_col);
	mR.setName('R');
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];
		}
	}
	return mR;
}

const Mtrx Mtrx::multiply(const Mtrx& mA)
{
	int i, j, k;
	Mtrx mR(n_row, mA.n_col);
	mR.setName('R');
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < mA.n_col; j++)
		{
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++)
			{
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];
			}
		}
	}
	return mR;
}