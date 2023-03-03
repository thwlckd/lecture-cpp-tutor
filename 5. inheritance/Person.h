#pragma once

#ifndef PERSON_H
#define PERSON_H

#include "Date.h"

using namespace std;

class Person
{
	friend ostream& operator<< (ostream&, const Person&);
public:
	Person();
	Person(string n, Date bd);
	void setName(string n) { name = n; }
	void setBirthDate(Date bd) { birthDate = bd; }
	string getName() const { return name; }
	Date getBirthDate() const { return birthDate; }
protected:
	Date birthDate;
	string name;
};
#endif