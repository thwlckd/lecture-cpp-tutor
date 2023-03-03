#pragma once

#include <iostream>
#include <iomanip>
#include<time.h>

using namespace std;

typedef struct s_Student
{
	int st_id;
	char name[16];
	char dept[16];
	int grade;
	double gpa;
} Student;

void initStudents(Student students[], int st_ids[], int num_students);
void printStudent(Student* pSt);
void printStudents(Student students[], int num_students);
void printStudentIDs(Student students[], int num_students);
void printBigArrayOfStudent_IDs(Student students[], int num_students, int num_first_last);
void selectionSortStudentsBy_ID(Student students[], int num_students);
void selectionSortStudentsByGPA_ID(Student students[], int num_students);
void printBigArrayOfStudent_GPA_IDs(Student students[], int num_students, int num_first_last);
Student* binarySearchStudentByID(Student students[], int num_students, int st_ID);