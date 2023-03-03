#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"

using namespace std;

// class StudentArray;
class Student : public Person
{
    friend class StudentArray;
    friend ostream& operator<< (ostream&, const Student&);
public:
    Student(); // default constructor
    Student(string n, Date dob, int id, string dept_n, double gpa);
    void setST_id(int id) { st_id = id; }
    void setDept_name(string dp_n) { dept_name = dp_n; };
    void setGPA(double g) { gpa = g; }
    int getST_id() { return st_id; }
private:
    int st_id;
    string dept_name;
    double gpa;
};
#endif