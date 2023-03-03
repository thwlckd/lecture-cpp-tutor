/*
*Lab2_21720956_박창협
*Author : 박창협
*Programed on September. 9. 2020
*class Date, class Person을 활용한 날짜 계산 및 생년월일 출력 프로그램
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

    fout.open("output.txt");  // txt파일 생성 및 오픈
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
    time(&currentTime);  // 1970년 1월 1일 자정부터 경과된 현재 시간을 초단위로 계산
    time_and_date = localtime(&currentTime);  // 현재 지역시간을 struct tm의 형식으로 가져옴
    year = time_and_date->tm_year + 1900;  // tm_year: 1900년도부터 카운트하기 때문에 이번년도를 나타내기 위한 +1900
    month = time_and_date->tm_mon + 1;  // tm_mon: 0~11 -> 12개월을 나타내기 위한 +1
    day = time_and_date->tm_mday;  // 일 저장
    Date newYearDay(year, 1, 1), today(year, month, day);
    fout << "AD Jan. 1, 1 is ";
    AD010101.fprintDate(fout);  // AD010101 출력
    fout << endl;
    fout << "Today is ";
    today.fprintDate(fout);  // 오늘 날짜 출력
    fout << endl;
    fout << "New year's day of this year was ";
    newYearDay.fprintDate(fout);  // 올해 1월 1일 출력
    fout << endl;
    Date christmas(year, 12, 25);
    fout << "Christmas of this year is ";
    christmas.fprintDate(fout);  // 크리스마스 출력
    fout << endl;
    if (today.getMonth() == christmas.getMonth() && today.getDay() == christmas.getDay())  // 오늘이 크리스마스 이면
    {
        fout << "Today is Christmas! Happy Christmas to you all !!\n";
    }
    else  // 크리스마스가 아니면
    {
        fout << " Sorry, today is not Christmas!\n";
        daysToChristmas = christmas.getElapsedDaysFromAD010101() - today.getElapsedDaysFromAD010101();
        fout << " You must wait " << daysToChristmas << " day(s) to Christmas !" << endl;
    }
    fout << endl;

    /* part 2 - handling class Person */
    Person p1(string("Park, Chagn - Hyub"), Date(1998, 3, 14)), p2;
    fout << "Person p1 : " << endl;
    p1.fprintPerson(fout);  // p1(Park, Chagn - Hyub) 의 생일 출력
    fout << endl;
    fout << "Person p2 : " << endl;
    p2.setName(string("Lee, Soo - Jeong"));
    p2.setBirthDate(Date(2018, 9, 1));
    p2.fprintPerson(fout);  // p2(Lee, Soo - Jeong) 의 생일 출력
    fout << endl;
    fout << endl << "Generating array of persons ... " << endl;
    Person* persons;
    persons = (Person*) new Person[NUM_PERSON];  // NUM_PERSON 만큼의 클래스 배열 person 동적 생성
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