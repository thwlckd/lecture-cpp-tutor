/*
*Lab3_21720956_��â��
*Author : ��â��
*Programed on September. 16, 2020
*���Ϸκ��� �Է¹��� �ΰ��� Mtrx �����͸� �����ϴ� ���α׷�
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
   
    Mtrx mtrxA(fin);  // ������ Mtrx�� ũ�⿡ ���� 2���� �迭�� ���� �Ҵ� �� 2���� �迭 ������ A �޾ƿ�
    mtrxA.setName('A');
    fout << " MtrxA:\n";
    mtrxA.fprintMtrx(fout);
    Mtrx mtrxB(fin);  // mtrxA�� ���� ������� mtrxB�� �޾ƿ�
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