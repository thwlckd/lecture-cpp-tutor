#include"Mtrx.h"
#include<iomanip>

ostream& operator<< (ostream& fout, const Mtrx& mtx)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2, a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;  // 확장 완성형 코드 사용하기 위한 변수 선언
	fout << mtx.name << endl;  // 행렬 이름 출력
	for (int i = 0; i < mtx.n_row; i++)
	{
		for (int j = 0; j < mtx.n_col; j++)
		{
			fout << fixed << setprecision(2);
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa3: ┌
			else if ((i == 0) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a4;  // 0xa6, 0xa4:  ┐
			else if ((i > 0) && (i < (mtx.n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa2: │(table 좌측에 출력) 
			else if ((i > 0) && (i < (mtx.n_row - 1)) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a2;  // 0xa6, 0xa2: │(table 우측에 출력)
			else if ((i == (mtx.n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa6: └
			else if ((i == (mtx.n_row - 1)) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a5;  // 0xa6, 0xa5:  ┘
			else
				fout << setw(6) << mtx.dM[i][j];
		}
		fout << endl;
	}
	fout << endl;

	return fout;
}

istream& operator>> (istream& fin, Mtrx& mtx)
{
	fin >> mtx.n_row >> mtx.n_col;  // 파일로 부터 행렬의 크기 받아옴
	for (int i = 0; i < mtx.n_row; i++)
	{
		for (int j = 0; j < mtx.n_col; j++)
			fin >> mtx.dM[i][j];  // 각 행/렬 위치의 값을 받아옴
	}

	return fin;
}

Mtrx::Mtrx()
{
	this->n_row = 0;
	this->n_col = 0;
}

Mtrx::Mtrx(string nm, int num_row, int num_col)
{
	int i, j;
	set_name(nm);
	n_row = num_row;
	n_col = num_col;
	dM = new double* [num_row];  // 행의 크기만큼 1차원 배열 동적 할당

	for(i = 0; i < num_row; i++)
	{
		dM[i] = new double[n_col];  // 열의 크기만큼 2차원 배열 동적 할당
	}
	for(i = 0; i < num_row; i++)
	{
		for(j = 0; j < num_col; j++)
		{
			dM[i][j] = 0.0;  // 생성 배열 초기화
		}
	}
}

Mtrx::Mtrx(string nm, double* pA, int num_row, int num_col)
{
	int i, j, cnt;
	set_name(nm);
	n_row = num_row;
	n_col = num_col;
	dM = new double* [n_row];
	for(i = 0; i < n_row; i++)
	{
		dM[i] = new double[n_col];
	}
	cnt = 0;
	for(i = 0; i < n_row; i++)
		for(j = 0; j < n_col; j++)
		{
			if(cnt < n_row * n_col)  // 배열의 인덱스 만큼 값을 복사
				dM[i][j] = pA[cnt++];
			else  // 나머지는 0으로 초기화
				dM[i][j] = 0.0;
		}
}

Mtrx::Mtrx(istream& fin)
{
	int i, j, num_row, num_col;
	double d;
	fin >> num_row >> num_col;
	n_row = num_row;
	n_col = num_col;
	dM = new double* [num_row];  // 행의 크기만큼 1차원 배열 동적 할당

	for(i = 0; i < num_row; i++)
	{
		dM[i] = new double[n_col];  // 열의 크기만큼 2차원 배열 동적 할당
	}
	for(i = 0; i < num_row; i++)
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

Mtrx::~Mtrx()
{
	/* 동적 메모리 반납
	for (int i=0; i<n_row; i++)
		delete [] dM[i];
	delete [] dM;
	*/
}

void Mtrx::init(int num_row, int num_col)
{
	int i, j;
	n_row = num_row;
	n_col = num_col;
	dM = new double* [n_row];  // 행의 크기만큼 1차원 배열 동적 할당

	for(i = 0; i < n_row; i++)
		dM[i] = new double[n_col];  // 열의 크기만큼 2차원 배열 동적 할당
	for(i = 0; i < n_row; i++)
		for (j = 0; j < n_col; j++)
			dM[i][j] = 0.0;  // 생성 배열 초기화
}

const Mtrx Mtrx::operator+(const Mtrx& mtx)
{
	int i, j;
	Mtrx mR("R", n_row, n_col);
	for(i = 0; i < n_row; i++)
	{
		for(j = 0; j < n_col; j++)
		{
			mR.dM[i][j] = this->dM[i][j] + mtx.dM[i][j];  // 2차원 배열 + 연산
		}
	}
	return mR;
}


const Mtrx Mtrx::operator-(const Mtrx& mtx)
{
	int i, j;
	Mtrx mR("R", n_row, n_col);
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			mR.dM[i][j] = dM[i][j] - mtx.dM[i][j];
		}
	}
	return mR;
}


const Mtrx Mtrx::operator*(const Mtrx& mtx)
{
	int i, j, k;
	Mtrx mR("R", n_row, mtx.n_col);
	for (i = 0; i < n_row; i++)
	{
		for (j = 0; j < mtx.n_col; j++)
		{
			mR.dM[i][j] = 0.0;
			for (k = 0; k < n_col; k++)
			{
				mR.dM[i][j] += dM[i][k] * mtx.dM[k][j];
			}
		}
	}
	return mR;
}

bool Mtrx::operator==(const Mtrx& mtx)
{
	Mtrx mR("R", n_row, n_col);

	if ((n_row != mtx.n_row) || (n_col != mtx.n_col))
		return false;

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			if (dM[i][j] != mtx.dM[i][j])
				return false;
		}
	}
	return true;
}

bool Mtrx::operator!=(const Mtrx& mtx)
{
	Mtrx mR("R", n_row, n_col);

	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			if (dM[i][j] != mtx.dM[i][j])
				return true;
		}
	}
	return false;
}


const Mtrx& Mtrx::operator= (const Mtrx& right)
{
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++)
		{
			this->dM[i][j] = right.dM[i][j];
		}
	}
	return *this;
}