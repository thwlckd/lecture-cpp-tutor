#include "Date.h"
#include<iomanip>

enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };  // 요일 열거형. 0~6

istream& operator>>(istream& input, Date& d)
{
	cout << "month : ";
	input >> d.month;
	cout << "day : ";
	input >> d.day;

	return input;
}

ostream& operator<<(ostream& output, const Date& d)
{
	//const char* weekDayName[7] = { "Sunday","Monday", "Tuesday", "Wednesday","Thursday", "Friday", "Saturday" };
	//const char* monthName[13] = { "", "January","February", "March", "April", "May","June", "July", "August", "September","October", "November", "December" };
	int yearDay = 0;
	int weekDay;

	output << d.year << "." << setw(2) << d.month << "." << setw(2) << d.day;

	/*if ((d.month >= 1) && (d.month <= 12))
		output << string(monthName[d.month]);  // 해당 달의 문자열 출력
	output << " " << d.day << ", " << d.year;*/

	//weekDay = getWeekDay();  // d.getWeekDay() 안되는 이유? : const
	//output << " (" << string(weekDayName[weekDay]) << ")";  // 해당 요일의 문자열 출력

	return output;
}

Date::Date()
{
	year = 0;
	month = 0;
	day = 0;
}

Date::Date(int y, int m, int d)
{
	year = y;
	month = m;
	day = d;
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

int Date::getYearDay()
{
	int yearDay = 0;
	yearDay = getYearDay(month, day);

	return yearDay;
}

int Date::getYearDay(int m, int d)
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

	elapsedDays = getElapsedDays();
	weekDay = elapsedDays % 7;  // 0~6 : Sunday~Saturday

	return weekDay;
}

int Date::getElapsedDays()
{
	int elpsDay = 0;
	elpsDay = getElapsedDays(*this);

	return elpsDay;
}

int Date::getElapsedDays(Date d)
{
	int yearDay;
	int elpsDay = 0;

	for (int y = 1; y < d.year; y++)
	{
		elpsDay += isLeapYear(y) ? 366 : 365;  // 윤년 366, 일반년 365
	}
	yearDay = getYearDay(d.month, d.day);
	elpsDay += yearDay;

	return elpsDay;
}

const Date& Date::operator=(const Date& rightSide)
{
	year = rightSide.year;
	month = rightSide.month;
	day = rightSide.day;

	return *this;
}

bool Date::operator>(const Date rightSide)
{
	if (getElapsedDays() > getElapsedDays(rightSide))
		return true;
	else
		return false;
}

bool Date::operator>=(const Date rightSide)
{
	if (getElapsedDays() >= getElapsedDays(rightSide))
		return true;
	else
		return false;
}

bool Date::operator<(const Date rightSide)
{
	if (getElapsedDays() < getElapsedDays(rightSide))
		return true;
	else
		return false;
}

bool Date::operator<=(const Date rightSide)
{
	if (getElapsedDays() <= getElapsedDays(rightSide))
		return true;
	else
		return false;
}

bool Date::operator==(const Date rightSide)
{
	if (getElapsedDays() == getElapsedDays(rightSide))
		return true;
	else
		return false;
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
