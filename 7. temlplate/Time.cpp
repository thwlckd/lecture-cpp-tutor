#include "Time.h"

ostream& operator<<(ostream& ostr, const Time& t)
{
	ostr << "(" << setw(2) << t.hour << ":" << setw(2) << t.min << ":" << setw(2) << t.sec << ")";

	return ostr;
}

Time::Time()
{
	hour = 0;
	min = 0;
	sec = 0;
}

Time::Time(int h, int m, int s)
{
	hour = h;
	min = m;
	sec = s;
}

Time& Time::operator+(int s)
{
	if ((sec + s) < 60)  // sec + s 가 59초보다 작을때
		sec = sec + s;
	else  // sec + s 가 59초 넘을때
	{
		min = min + (sec + s) / 60;  // 초를 분으로 환산해 min에 더해줌
		sec = (sec + s) % 60;  // 59가 넘어가는 초를 0부터 다시 시작
		if (min >= 60)  // 증가한 min이 59분을 넘을때
		{
			hour = hour + min / 60;  // 분을 시로 환산해 hour에 더해줌
			min = min % 60;  // 59가 넘어가는 분를 0부터 다시 시작
			hour = hour % 24;  // 23을 넘어가는 시를 0부터 다시 시작
		}
	}

	return *this;
}

int Time::elasedSec() const
{
	Time time;
	int elapsed_sec;

	time.hour = hour * 3600;
	time.min = min * 60;
	time.sec = sec;
	elapsed_sec = time.hour + time.min + time.sec;  // 00:00:00 부터 경과 시간을 초단위로 저장

	return elapsed_sec;
}

Time Time::getTime()
{
	return *this;
}

bool Time::operator<(const Time& t)
{
	int elapsed_sec1, elapsed_sec2;
	elapsed_sec1 = this->elasedSec();
	elapsed_sec2 = t.elasedSec();

	if (elapsed_sec1 < elapsed_sec2)
		return true;
	else
		return false;
}

bool Time::operator<=(const Time& t)
{
	int elapsed_sec1, elapsed_sec2;
	elapsed_sec1 = this->elasedSec();
	elapsed_sec2 = t.elasedSec();

	if (elapsed_sec1 <= elapsed_sec2)
		return true;
	else
		return false;
}

bool Time::operator>(const Time& t)
{
	int elapsed_sec1, elapsed_sec2;
	elapsed_sec1 = this->elasedSec();
	elapsed_sec2 = t.elasedSec();

	if (elapsed_sec1 > elapsed_sec2)
		return true;
	else
		return false;
}

bool Time::operator>=(const Time& t)
{
	int elapsed_sec1, elapsed_sec2;
	elapsed_sec1 = this->elasedSec();
	elapsed_sec2 = t.elasedSec();

	if (elapsed_sec1 >= elapsed_sec2)
		return true;
	else
		return false;
}

bool Time::operator==(const Time& t)
{
	int elapsed_sec1, elapsed_sec2;
	elapsed_sec1 = this->elasedSec();
	elapsed_sec2 = t.elasedSec();

	if (elapsed_sec1 == elapsed_sec2)
		return true;
	else
		return false;
}

bool Time::isValidTime(int h, int m, int s)
{
	if ((h < 0) || (h > 24) || (m < 0) || (m > 59) || (s < 0) || (s > 59))
		return false;
	else
		return true;
}
