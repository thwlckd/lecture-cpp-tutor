/*
*Lab4_21720956_박창협
*Author : 박창협
*Programed on September. 22. 2020
*배열 클래스를 이용한 연산자 오버로딩 프로그램
*/
#include <iostream>
#include <fstream>
#include "Mtrx.h"
#include "MtrxArray.h"

#define NUM_ROW 7
#define NUM_COL 7
#define NUM_MTRX 6

using namespace std;

int main()
{
    ifstream fin;
    ofstream fout;
    fin.open("Matrix_7x7.txt");
    if (fin.fail())
    {
        cout << "Error in opening input data file !!" << endl;
        exit;
    }
    fout.open("Result.txt");
    if (fout.fail())
    {
        cout << "Error in opening output data file !!" << endl;
        exit;
    }
    MtrxArray mtrx(NUM_MTRX, NUM_ROW, NUM_COL);
    fin >> mtrx[0];
    fin >> mtrx[1];
    mtrx[0].set_name("mtrx[0] =");
    mtrx[1].set_name("mtrx[1] =");
    fout << mtrx[0] << endl;
    fout << mtrx[1] << endl;
    mtrx[2] = mtrx[0] + mtrx[1];
    mtrx[2].set_name("mtrx[2] = mtrx[0] + mtrx[1] =");
    fout << mtrx[2] << endl;
    mtrx[3] = mtrx[0] - mtrx[1];
    mtrx[3].set_name("mtrx[3] = mtrx[0] - mtrx[1] =");
    fout << mtrx[3] << endl;
    mtrx[4] = mtrx[0] * mtrx[1];
    mtrx[4].set_name("mtrx[4] = mtrx[0] * mtrx[1] =");
    fout << mtrx[4] << endl;
    mtrx[5] = mtrx[0];
    mtrx[5].set_name("mtrx[5] = mtrx[0] =");
    fout << mtrx[5] << endl;
    if (mtrx[0] == mtrx[1])
        fout << "mtrx[0] and mtrx[1] are equal.\n";
    if (mtrx[0] != mtrx[1])
        fout << "mtrx[0] and mtrx[1] are not equal.\n";
    fin.close();
    fout.close();
    return 0;
}