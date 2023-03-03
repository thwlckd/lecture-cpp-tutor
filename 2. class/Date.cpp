#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };  // 요일 열거형. 0~6

Date::Date() //default constructor
{
	year = 0; 
	month = 0;
	day = 0;
}

//default destructor
Date::~Date()
{
	// cout << "Date object instance is destructed" << endl;
}

//constructor with given arguments
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

void Date::setYear(int y)
{
	year = y;
}

void Date::setMonth(int newMonth)
{
	if ((newMonth >= 1) && (newMonth <= 12))
		month = newMonth;
	else
	{
		cout << "Illegal month value! Program aborted. \n";
		exit(1);
	}
	day = 1;  // 새로운 달로 넘어가면 1일
}

void Date::setDate(int y, int m, int d)
{
	if (isValidDate(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else 
	{
		cout << "Invalid date (" << y << ", " << m << ", " << d << ")";
		cout << " Program aborted !!\n";
		exit(1);
	}
}

bool Date::isLeapYear(int y)
{
	if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) // 윤년조건
		return true;
	else
		return false;
}

bool Date::isLeapYear()
{
	return isLeapYear(year);
}

int Date::getYearDay()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31,30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())
		days_month[2] = 29;  // 윤년이면 2월달 29일 까지

	for (int m = 1; m < month; m++)
		yearDay += days_month[m];
	yearDay += day;

	return yearDay;
}

int Date:: getYearDay(int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31,30, 31, 31, 30, 31, 30, 31 };
	int yearDay = 0;

	if (isLeapYear())
		days_month[2] = 29;  // 윤년이면 2월달 29일 까지

	for (int mon = 1; mon < m; mon++)
		yearDay += days_month[mon];
	yearDay += d;

	return yearDay;
}

int Date::getWeekDay()
{
	int weekDay_AD010101 = MON;  // A.D 1년 1월 1일 (월)
	int weekDay;
	int elapsedDays = 0;

	elapsedDays = getElapsedDaysFromAD010101();
	weekDay = elapsedDays % 7;  // 0~6 : Sunday~Saturday

	return weekDay;
}
void Date::inputDate()
{
	int y, m, d;

	cout << "Enter date in year month day : ";
	cin >> y >> m >> d;  // 사용자로 부터 날짜 받아옴

	if (isValidDate(y, m, d))
	{
		year = y;
		month = m;
		day = d;
	}
	else
	{
		cout << "Ilegal date! Program aborted.\n";
		exit(1);
	}
}

bool Date::isValidDate(int y, int m, int d)
{
	int days_month[13] = { 0, 31, 28, 31, 30,31, 30, 31, 31, 30, 31, 30, 31 };

	if (isLeapYear(y))
		days_month[2] = 29;
	if ((m >= 1) && (m <= 12) && (d >= 1) && (d <= days_month[m]))
		return true;
	else
	{
		cout << "Ilegal date! (" << m << ", " << d << ") ==> Program aborted.\n";
		return false;
	}
}

void Date::setRandDateAttributes()
{
	int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	year = rand() % 2000 + 1000;  // 1000~2999
	month = rand() % 12 + 1;  // 1~12
	if (isLeapYear(year) && month == 2)
		days_month[2] = 29;
	day = rand() % days_month[month] + 1;  // 0~days_month[month]
}

void Date:: fprintDate(ostream& fout)
{
	const char* weekDayName[7] = { "Sunday","Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" };
	const char* monthName[13] = { "", "January","February", "March", "April", "May","June", "July", "August", "September","October", "November", "December" };
	int yearDay = 0;
	int weekDay;

	if ((month >= 1) && (month <= 12))
		fout << string(monthName[month]);  // 해당 달의 문자열 출력
	fout << " " << day << ", " << year;
	yearDay = getYearDay();
	weekDay = getWeekDay();
	fout << " (" << string(weekDayName[weekDay]) << ")";  // 해당 요일의 문자열 출력
}

int Date::getElapsedDaysFromAD010101()
{

	int elpsDay = 0;

	elpsDay = getElapsedDaysFromAD010101(*this);

	return elpsDay;
}

int Date::getElapsedDaysFromAD010101(Date d)
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 1; y < year; y++)
	{
		elpsDay += isLeapYear(y) ? 366 : 365;  // 윤년 366, 일반년 365
	}
	yearDay = getYearDay(d.month, d.day);
	elpsDay += yearDay;

	return elpsDay;
}
