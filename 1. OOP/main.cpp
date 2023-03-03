/*
*Lab1_21720956_박창협
*Author : 박창협
*Programed on September. 4. 2020
*큰 난수 배열의 생성 및 Student 구조체의 정렬 및 탐색
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include "Student.h"
using namespace std;

#define NUM_STUDENTS 5000
#define NUM_SEARCH 5
#define NUM_FIRST_LAST_BLOCK 100

void genBigRandArray(int randArray[], int num_rands);

void main()
{
	int* student_ids;
	Student* students, * pSt;
	int studentID_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };
	
	student_ids = (int*)malloc(sizeof(int) * NUM_STUDENTS);
	students = (Student*)malloc(sizeof(Student) * NUM_STUDENTS);
	genBigRandArray(student_ids, NUM_STUDENTS);
	initStudents(students, student_ids, NUM_STUDENTS);
	cout << endl << endl;
	cout << "Initialized array of students : " << endl;
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	cout << endl << endl;
	cout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	cout << endl << endl;
	cout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	selectionSortStudentsByGPA_ID(students, NUM_STUDENTS); // non-increasing order
	printBigArrayOfStudent_GPA_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	cout << endl << endl;
	cout << "Sorting array of students by non-decreasing order of ID : " << endl;
	selectionSortStudentsBy_ID(students, NUM_STUDENTS);
	printBigArrayOfStudent_IDs(students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	cout << endl << endl;
	cout << "Searching student with student_ID : " << endl;
	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = binarySearchStudentByID(students, NUM_STUDENTS, studentID_search[i]);
		cout << "Student search by ID (" << setw(4) << studentID_search[i] << ") : ";
		if (pSt != NULL)
			printStudent(pSt);
		else
			cout << "NULL - student was not found !!";
		cout << endl;
	}

}

void genBigRandArray(int randArray[], int num_rands)
{
	char* flag;
	int count = 0;
	unsigned int u_int32 = 0;
	unsigned int bigRand;
	flag = (char*)calloc(sizeof(char), num_rands);
	//flag = new char[num_rands];
	while (count < num_rands)
	{
		u_int32 = ((long)rand() << 15) | rand();
		bigRand = u_int32 % num_rands;
		if (flag[bigRand] == 1) 
		{
			continue;
		}
		flag[bigRand] = 1;
		randArray[count++] = bigRand;
	}
}

