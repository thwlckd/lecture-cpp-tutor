#pragma once

#ifndef PERSON_H
#define PERSON_H

#include"Date.h"

using namespace std;

class Person
{
    friend ostream& operator<< (ostream&, const Person&);
public:
    Person();
    Person(string n, Date dob);
    void setName(string n) { name = n; }

    string getName() { return name; }
protected:
    Date dateOfBirth;
    string name;
};

#endif