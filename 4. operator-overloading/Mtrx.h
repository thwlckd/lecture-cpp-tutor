#pragma once

#ifndef MTRX_H
#define MTRX_H

#include<iostream>
#include <string>

using namespace std;

class MtrxArray;
class Mtrx
{
    friend ostream& operator<< (ostream&, const Mtrx&);
    friend istream& operator>> (istream&, Mtrx&);
    friend class MtrxArray;
public:
    Mtrx(); // default constructor
    Mtrx(string nm, int n_row, int n_col);
    Mtrx(string nm, double* pA, int n_row, int n_col);
    Mtrx(istream& fin);
    ~Mtrx();
    void init(int n_row, int n_col);
    void set_name(string nm) { name = nm; }
    string get_name() { return name; }
    int get_n_row() const { return n_row; }
    int get_n_col() const { return n_col; }
    const Mtrx operator+(const Mtrx&);
    const Mtrx operator-(const Mtrx&);
    const Mtrx operator*(const Mtrx&);
    const Mtrx& operator=(const Mtrx&);
    bool operator==(const Mtrx&);
    bool operator!=(const Mtrx&);
private:
    string name;
    int n_row;
    int n_col;
    double** dM;
};
#endif