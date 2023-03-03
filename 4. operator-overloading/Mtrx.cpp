#include"Mtrx.h"
#include<iomanip>

ostream& operator<< (ostream& fout, const Mtrx& mtx)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2, a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;  // Ȯ�� �ϼ��� �ڵ� ����ϱ� ���� ���� ����
	fout << mtx.name << endl;  // ��� �̸� ���
	for (int i = 0; i < mtx.n_row; i++)
	{
		for (int j = 0; j < mtx.n_col; j++)
		{
			fout << fixed << setprecision(2);
			if ((i == 0) && (j == 0))
				fout << a6 << a3 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa3: ��
			else if ((i == 0) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a4;  // 0xa6, 0xa4:  ��
			else if ((i > 0) && (i < (mtx.n_row - 1)) && (j == 0))
				fout << a6 << a2 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa2: ��(table ������ ���) 
			else if ((i > 0) && (i < (mtx.n_row - 1)) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a2;  // 0xa6, 0xa2: ��(table ������ ���)
			else if ((i == (mtx.n_row - 1)) && (j == 0))
				fout << a6 << a6 << setw(6) << mtx.dM[i][j];  // 0xa6, 0xa6: ��
			else if ((i == (mtx.n_row - 1)) && (j == (mtx.n_col - 1)))
				fout << setw(6) << mtx.dM[i][j] << a6 << a5;  // 0xa6, 0xa5:  ��
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
	fin >> mtx.n_row >> mtx.n_col;  // ���Ϸ� ���� ����� ũ�� �޾ƿ�
	for (int i = 0; i < mtx.n_row; i++)
	{
		for (int j = 0; j < mtx.n_col; j++)
			fin >> mtx.dM[i][j];  // �� ��/�� ��ġ�� ���� �޾ƿ�
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
	dM = new double* [num_row];  // ���� ũ�⸸ŭ 1���� �迭 ���� �Ҵ�

	for(i = 0; i < num_row; i++)
	{
		dM[i] = new double[n_col];  // ���� ũ�⸸ŭ 2���� �迭 ���� �Ҵ�
	}
	for(i = 0; i < num_row; i++)
	{
		for(j = 0; j < num_col; j++)
		{
			dM[i][j] = 0.0;  // ���� �迭 �ʱ�ȭ
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
			if(cnt < n_row * n_col)  // �迭�� �ε��� ��ŭ ���� ����
				dM[i][j] = pA[cnt++];
			else  // �������� 0���� �ʱ�ȭ
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
	dM = new double* [num_row];  // ���� ũ�⸸ŭ 1���� �迭 ���� �Ҵ�

	for(i = 0; i < num_row; i++)
	{
		dM[i] = new double[n_col];  // ���� ũ�⸸ŭ 2���� �迭 ���� �Ҵ�
	}
	for(i = 0; i < num_row; i++)
	{
		for (j = 0; j < n_col; j++)
		{
			if (fin.eof())
				dM[i][j] = 0.0;
			else
			{
				fin >> d;  // ���Ϸκ��� ���� �޾ƿ�
				dM[i][j] = d;  // 2���� �迭�� �Ҵ�
			}
		}
	}
}

Mtrx::~Mtrx()
{
	/* ���� �޸� �ݳ�
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
	dM = new double* [n_row];  // ���� ũ�⸸ŭ 1���� �迭 ���� �Ҵ�

	for(i = 0; i < n_row; i++)
		dM[i] = new double[n_col];  // ���� ũ�⸸ŭ 2���� �迭 ���� �Ҵ�
	for(i = 0; i < n_row; i++)
		for (j = 0; j < n_col; j++)
			dM[i][j] = 0.0;  // ���� �迭 �ʱ�ȭ
}

const Mtrx Mtrx::operator+(const Mtrx& mtx)
{
	int i, j;
	Mtrx mR("R", n_row, n_col);
	for(i = 0; i < n_row; i++)
	{
		for(j = 0; j < n_col; j++)
		{
			mR.dM[i][j] = this->dM[i][j] + mtx.dM[i][j];  // 2���� �迭 + ����
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