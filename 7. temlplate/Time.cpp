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
	if ((sec + s) < 60)  // sec + s �� 59�ʺ��� ������
		sec = sec + s;
	else  // sec + s �� 59�� ������
	{
		min = min + (sec + s) / 60;  // �ʸ� ������ ȯ���� min�� ������
		sec = (sec + s) % 60;  // 59�� �Ѿ�� �ʸ� 0���� �ٽ� ����
		if (min >= 60)  // ������ min�� 59���� ������
		{
			hour = hour + min / 60;  // ���� �÷� ȯ���� hour�� ������
			min = min % 60;  // 59�� �Ѿ�� �и� 0���� �ٽ� ����
			hour = hour % 24;  // 23�� �Ѿ�� �ø� 0���� �ٽ� ����
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
	elapsed_sec = time.hour + time.min + time.sec;  // 00:00:00 ���� ��� �ð��� �ʴ����� ����

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
