#pragma once

#ifndef STUDENT_H
#define STUDENT_H

#include"Person.h"
#include"Time.h"

using namespace std;

class Student : public Person
{
	friend ostream& operator<< (ostream&, const Student&);
public:
	Student(); // default constructor
	Student(int id, string n, Date bod, Time avt, double gpa);
	int getST_id() { return st_id; }
	double getGPA() { return gpa; }
	Time getArrTime() { return arrivalTime; }
	void setST_id(int id) { st_id = id; }
	void setGPA(double g) { gpa = g; }
	void setArrivalTime(Time t) { arrivalTime = t; }
	Time getArrivalTime() { return arrivalTime; }
private:
	int st_id;
	double gpa;
	Time arrivalTime;
};

#endif