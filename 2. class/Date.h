#pragma once

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#define WEEKDAY_AD01Jan01 MON // the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute * 60)
#define Secs_in_DAY (Secs_in_Hour * 24)
#define LOCAL_GMT_OFFSET_HOUR 9

class Date
{
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	~Date(); // destructor
	void inputDate();
	void fprintDate(ostream& fout);
	void setDate(int y, int m, int dy);
	void setRandDateAttributes();  // ������ ��, ��, �� �����ϴ� �Լ�
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDaysFromAD010101(); //  AD 1. 1. 1. �� ���� ���� �ϼ� �޾ƿ��� �Լ�
	int getElapsedDaysFromAD010101(Date d);

private:
	bool isLeapYear();  // ���� �Ǻ� �Լ�
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);  // ��ȿ�� ��¥���� �Ǻ��ϴ� �Լ�
	int year;
	int month;
	int day;
};
#endif 