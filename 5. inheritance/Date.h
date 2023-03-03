#pragma once

#ifndef DATE_H
#define DATE_H

#include <iostream>

using namespace std;

class Date
{
	friend istream& operator>>(istream&, Date&);
	friend ostream& operator<<(ostream&, const Date&);
	friend class DateArray;
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	void setDate(int newYear, int newMonth, int newDay);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	int getDay() const { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDays(); // get elapsed days from AD 1. 1. 1.
	int getElapsedDays(Date d);
	const Date& operator=(const Date& rightSide);
	bool operator>(const Date rightSide);
	bool operator<(const Date rightSide);
	bool operator==(const Date rightSide);
	bool isLeapYear(int y); // check whether the given year y is leap year
private:
	bool isLeapYear(); // check whether the year is leap year
	bool isValidDate(int y, int m, int d);
	int year;
	int month;
	int day;
};
#endif