/*
*Lab2_21720956_��â��
*Author : ��â��
*Programed on September. 9. 2020
*class Date, class Person�� Ȱ���� ��¥ ��� �� ������� ��� ���α׷�
*/

#include <iostream>
#include <fstream>
#include <time.h> // for time(), localtime(), time_t, struct tm
#include <string>
#include "Date.h"
#include "Person.h"

using namespace std;

#define NUM_PERSON 10

int main()
{
    ofstream fout;

    fout.open("output.txt");  // txt���� ���� �� ����
    if (fout.fail())
    {
        fout << "Error in opening output.txt !!" << endl;
        exit;
    }

    /* part 1 - handling class Date */
    Date AD010101(1, 1, 1);
    int year, month, day;
    int daysToChristmas;
    time_t currentTime;
    struct tm* time_and_date;
    time(&currentTime);  // 1970�� 1�� 1�� �������� ����� ���� �ð��� �ʴ����� ���
    time_and_date = localtime(&currentTime);  // ���� �����ð��� struct tm�� �������� ������
    year = time_and_date->tm_year + 1900;  // tm_year: 1900�⵵���� ī��Ʈ�ϱ� ������ �̹��⵵�� ��Ÿ���� ���� +1900
    month = time_and_date->tm_mon + 1;  // tm_mon: 0~11 -> 12������ ��Ÿ���� ���� +1
    day = time_and_date->tm_mday;  // �� ����
    Date newYearDay(year, 1, 1), today(year, month, day);
    fout << "AD Jan. 1, 1 is ";
    AD010101.fprintDate(fout);  // AD010101 ���
    fout << endl;
    fout << "Today is ";
    today.fprintDate(fout);  // ���� ��¥ ���
    fout << endl;
    fout << "New year's day of this year was ";
    newYearDay.fprintDate(fout);  // ���� 1�� 1�� ���
    fout << endl;
    Date christmas(year, 12, 25);
    fout << "Christmas of this year is ";
    christmas.fprintDate(fout);  // ũ�������� ���
    fout << endl;
    if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())  // ������ ũ�������� �̸�
    {
        fout << "Today is Christmas! Happy Christmas to you all !!\n";
    }
    else  // ũ���������� �ƴϸ�
    {
        fout << " Sorry, today is not Christmas!\n";
        daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();
        fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
    }
    fout << endl;

    /* part 2 - handling class Person */
    Person p1(string("Park, Chagn - Hyub"), Date(1998, 3, 14)), p2;
    fout << "Person p1 : " << endl;
    p1.fprintPerson(fout);  // p1(Park, Chagn - Hyub) �� ���� ���
    fout << endl;
    fout << "Person p2 : " << endl;
    p2.setName(string("Lee, Soo - Jeong"));
    p2.setBirthDate(Date(2018, 9, 1));
    p2.fprintPerson(fout);  // p2(Lee, Soo - Jeong) �� ���� ���
    fout << endl;
    fout << endl << "Generating array of persons ... " << endl;
    Person* persons;
    persons = (Person*) new Person[NUM_PERSON];  // NUM_PERSON ��ŭ�� Ŭ���� �迭 person ���� ����
    for (int i = 0; i < NUM_PERSON; i++)
    {
        persons[i].setRandPersonAttributes();
        persons[i].fprintPerson(fout);
        fout << endl;
    }
    fout << endl;
    delete[] persons;
    fout.close();

    return 0;
}