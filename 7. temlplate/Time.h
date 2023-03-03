#pragma once

#ifndef TIME_H
#define TIME_H

#include<iostream>
#include<iomanip>

using namespace std;

class Time
{
	friend ostream& operator<<(ostream&, const Time&);
public:
	Time(); // default constructor
	Time(int h, int m, int s);
	Time& operator+(int s);
	int elasedSec() const;
	Time getTime();
	bool operator<(const Time& right);
	bool operator<=(const Time& right);
	bool operator>(const Time& right);
	bool operator>=(const Time& right);
	bool operator==(const Time& right);
private:
	bool isValidTime(int, int, int);
	int hour;
	int min;
	int sec;
};

#endif