#pragma once

#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int n_row, int n_col);  // ��/���� ũ�⿡ ���� 2���� �迭�� ���� �����ϰ� �迭�� �ʱ�ȭ ��Ŵ
	Mtrx(istream& fin);  // ���Ϸκ��� �����͸� ���� 2���� �迭�� �����Ҵ� �ް� �� ���� ����
	~Mtrx(); // destructor
	void fprintMtrx(ostream& fout);
	void setName(char ch) { name = ch; };
	char getName() { return name; };
	int getN_row() { return n_row; }
	int getN_col() { return n_col; }
	const Mtrx add(const Mtrx&);
	const Mtrx sub(const Mtrx&);
	const Mtrx multiply(const Mtrx&);
private:
	char name;
	int n_row;
	int n_col;
	double** dM;
};
#endif