/*
*Lab3_21720956_박창협
*Author : 박창협
*Programed on September. 16, 2020
*파일로부터 입력받은 두개의 Mtrx 데이터를 연산하는 프로그램
*/

#include <iostream>
#include <fstream>
#include "Class_Mtrx.h"

using namespace std;

void main()
{
    ifstream fin;
    ofstream fout;
    int n_row, n_col;
    fin.open("Matrix_data.txt");
    if (fin.fail())
    {
        cout << "Error in opening Matrix_5x5_data.txt !!" << endl;
        exit;
    }
    fout.open("output.txt");
    if (fout.fail())
    {
        cout << "Error in opening Matrix_operations_results.txt !!" << endl;
        exit;
    }
   
    Mtrx mtrxA(fin);  // 파일의 Mtrx의 크기에 맞춰 2차원 배열의 동적 할당 및 2차원 배열 데이터 A 받아옴
    mtrxA.setName('A');
    fout << " MtrxA:\n";
    mtrxA.fprintMtrx(fout);
    Mtrx mtrxB(fin);  // mtrxA와 같은 방식으로 mtrxB도 받아옴
    mtrxB.setName('B');
    fout << " MtrxB:\n";
    mtrxB.fprintMtrx(fout);
    n_row = mtrxA.getN_row();
    n_col = mtrxB.getN_col();

    Mtrx mtrxC(n_row, n_col);
    mtrxC.setName('C');
    mtrxC = mtrxA.add(mtrxB);  // C = A + B
    fout << " MtrxC = mtrxA.add(mtrxB) :\n";
    mtrxC.fprintMtrx(fout);

    Mtrx mtrxD(n_row, n_col);
    mtrxD = mtrxA.sub(mtrxB);
    mtrxD.setName('D');  // D = A - B
    fout << " MtrxD = mtrxA.sub(mtrxB) :\n";
    mtrxD.fprintMtrx(fout);

    Mtrx mtrxE(n_row, n_col);
    mtrxE.setName('E');
    mtrxE = mtrxA.multiply(mtrxB);  // E = A X B
    fout << " MtrxE = mtrxA.multiply(mtrxB) :\n";
    mtrxE.fprintMtrx(fout);
    
    //cout << "size of Class matrix =" << sizeof(Mtrx) << endl;
    fout.close();
}