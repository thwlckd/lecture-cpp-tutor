#pragma once

#ifndef MTRX_H
#define MTRX_H

#include <iostream>
#include <fstream>

using namespace std;

#define MAX_SIZE 100

class Mtrx {
public:
	Mtrx(int n_row, int n_col);  // 행/렬의 크기에 맞춰 2차원 배열을 동적 생성하고 배열을 초기화 시킴
	Mtrx(istream& fin);  // 파일로부터 데이터를 받을 2차원 배열을 동적할당 받고 그 값을 저장
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