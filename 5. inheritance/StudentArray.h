#pragma once

#ifndef STUDENTARRAY_H
#define STUDENTARRAY_H

#include "Student.h"
#include "Date.h"

using namespace std;

class StudentArray
{
    friend ostream& operator<< (ostream&, const StudentArray&);
public:
    StudentArray(int size); // constructor
    StudentArray(const StudentArray& obj);
    ~StudentArray();
    int size() { return num_students; }
    Student& operator[](int index);
    void sortByBirthDate();
    void sortByName();
    void sortByST_ID();
    void sortByGPA();
private:
    Student* students;
    int num_students;
    bool isValidIndex(int index);
};
#endif