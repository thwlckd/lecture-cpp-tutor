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
	void setRandDateAttributes();  // 임의의 년, 월, 일 생성하는 함수
	void setMonth(int m);
	void setYear(int y);
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay();
	int getYearDay(int m, int d);
	int getWeekDay();
	int getElapsedDaysFromAD010101(); //  AD 1. 1. 1. 로 부터 누적 일수 받아오는 함수
	int getElapsedDaysFromAD010101(Date d);

private:
	bool isLeapYear();  // 윤년 판별 함수
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);  // 유효한 날짜인지 판별하는 함수
	int year;
	int month;
	int day;
};
#endif 