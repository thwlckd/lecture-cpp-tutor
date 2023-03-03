/*
*Lab5_21720956_��â��
*Author : ��â��
*Programed on December. 3. 2020
*��� ������ �̿��� class Date, class Person, class Student, class StudentArray Ȱ�� ���α׷�
*/

#include <iostream>
#include <fstream>
#include "StudentArray.h"
#include <string>

#define NUM_STUDENTS 5

Student genStudent();

void main()
{
    StudentArray studentArray(NUM_STUDENTS);
    Student st;
    ofstream fout;
    fout.open("output.txt");
    if (fout.fail())
    {
        cout << "Fail to open an output file (output.txt)\n";
        exit(1);
    }
    fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
    for (int i = 0; i < NUM_STUDENTS; i++)
    {
        st = genStudent();
        studentArray[i] = st;
    }
    fout << studentArray;
    fout << "\nSorting studentArray by student id : " << endl;
    studentArray.sortByST_ID();
    fout << studentArray;

    fout << "\nSorting studentArray by student name : " << endl;
    studentArray.sortByName();
    fout << studentArray;

    fout << "\nSorting studentArray by GPA : " << endl;
    studentArray.sortByGPA();
    fout << studentArray;

    fout << "\nSorting studentArray by BirthDate : " << endl;
    studentArray.sortByBirthDate();
    fout << studentArray;
    fout << endl;
    fout.close();
}

bool isLeapYear(int y)
{
    if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) // ��������
        return true;
    else
        return false;
}

Student genStudent()
{
    // st_id ������
    char* flag;
    int count = 0, rand_left, rand_right, bigrand, id;
    Student st;

    flag = (char*) new char[40001];
    while (count < 40001)
    {
        rand_left = rand();
        rand_right = rand();
        bigrand = (rand_left << 15) | rand_right;  // bigrand ������ ���� left bitwise
        id = bigrand % 40001;  // 0 ~ 40000
        if (flag[id] == 1)
            continue;
        else
        {
            flag[id] = 1;
            st.setST_id(id + 10000);  // offset 10000, st_id ���� : 10000 ~ 50000
            count++;
        }
    }
    delete[] flag;

    // name ������
    char name[8];
    int name_length;

    name_length = rand() % 4 + 4;  // 4~7
    name[0] = rand() % 26 + 'A';  // �̸� ù���� �빮��
    for (int i = 1; i < name_length; i++)
        name[i] = rand() % 26 + 'a';  // ������ ���� �ҹ���
    name[name_length] = NULL;
    st.setName(name);

    // birthday ������
    int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }, year, month, day;
    Date birthday;

    year = rand() % 1000 + 2000;  // 2000~2999
    month = rand() % 12 + 1;  // 1~12
    if (isLeapYear(year) && month == 2)
        days_month[2] = 29;
    day = rand() % days_month[month] + 1;  // days_month �迭���� �޿� �´� ��¥ ����
    birthday.setDate(year, month, day);
    st.setBirthDate(birthday);

    //dep_name ������
    char dep[5];
    int dep_length;

    dep_length = rand() % 2 + 3;  // 3~4
    for (int i = 0; i < dep_length; i++)
    {
        dep[i] = rand() % 26 + 'A';
    }
    dep[dep_length] = NULL;
    st.setDept_name(dep);

    //GPA ������
    double gpa;
    gpa = (rand() % 10000) / (double)100;  // 0.00~99.99
    st.setGPA(gpa);

    return st;
}