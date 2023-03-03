#include"Student.h"

void initStudents(Student students[], int st_ids[], int num_students)
{
	int name_len;
	int j, grade;

	srand(time(0));
	for (int i = 0; i < num_students; i++)
	{
		students[i].st_id = st_ids[i];
		name_len = rand() % 11 + 5;
		students[i].name[0] = rand() % 26 + 'A';
		for (j = 1; j < name_len; j++)
			students[i].name[j] = rand() % 26 + 'a';
		students[i].name[j] = '\0';
		name_len = rand() % 4 + 2;
		for (j = 0; j < name_len; j++)
			students[i].dept[j] = rand() % 26 + 'A';
		students[i].dept[j] = '\0';
		students[i].grade = rand() % 8 + 1;
		students[i].gpa = (rand() % 10000) / 100.0;
	}
}

void printStudent(Student* pSt)
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "Student(ID: " << setw(4) << pSt->st_id;
	cout << ", Name: " << setw(16) << pSt->name;
	cout << ", Dept : " << setw(6) << pSt->dept;
	cout << ", Grade : " << pSt->grade;
	cout << ", GPA : " << pSt->gpa;
}

void printStudents(Student students[], int num_students)
{
	for (int i = 0; i < num_students; i++)
	{
		printStudent(students);  // Student의 각 멤버 데이터 출력하는 함수 호출
		printf("\n");
		students++;
	}
}

void printStudentIDs(Student students[], int num_students)
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << setw(4) << students->st_id;

}

void printStudentGPA_ID(Student students[], int num_students)
{
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);
	cout << "(" << setw(4) << students->st_id << students->gpa << ")";
}


void selectionSortStudentsBy_ID(Student students[], int num_students)
{
	int i, j, mx;
	char minName[16] = { 0 };
	Student tmp;
	int min_st, min_ID;
	for (i = 0; i < num_students - 1; i++)
	{
		min_st = i;
		min_ID = students[min_st].st_id;
		for (j = i + 1; j < num_students; j++)
		{
			if (students[j].st_id < min_ID)
			{
				min_st = j;
				min_ID = students[j].st_id;
			}
		}
		if (min_st != i)
		{
			tmp = students[i];
			students[i] = students[min_st];
			students[min_st] = tmp;
		}
	}
}

void selectionSortStudentsByGPA_ID(Student students[], int num_students)
{
	Student* pST, * pST_max;
	Student temp;
	int st_max_gpa;

	for (int i = 0; i < num_students; i++)
	{
		pST_max = &students[i];
		st_max_gpa = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pST = &students[j];
			if (pST_max->gpa < pST->gpa)  // 더 높은 학점 발견시
			{
				pST_max = pST;  // 해당값으로 pST_max 변경
				st_max_gpa = j;
			}
		}
		if (st_max_gpa != i)
		{
			/* i번째 구조체의 학점보다 높은 학점 발견시, i번째와 st_max_gpa번째 구조체 교환*/
			temp = students[st_max_gpa];
			students[st_max_gpa] = students[i];
			students[i] = temp;
		}
	}
}


/*
void selectionSortStudentsByGPA_ID(Student students[], int num_students)
{
	Student* pST, * pST_min;
	Student temp;
	int st_min_gpa;

	for (int i = 0; i < num_students; i++)
	{
		pST_min = &students[i];
		st_min_gpa = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pST = &students[j];
			if (pST_min->gpa > pST->gpa)  // 더 skw은 학점 발견시
			{
				pST_min = pST;  // 해당값으로 pST_min 변경
				st_min_gpa = j;
			}
		}

		if (st_min_gpa != i)
		{
			/* i번째 구조체의 학점보다 낮은 학점 발견시, i번째와 st_min_gpa번째 구조체 교환*/
/*
			temp = students[st_min_gpa];
			students[st_min_gpa] = students[i];
			students[i] = temp;
		}
	}
}
*/

Student* binarySearchStudentByID(Student students[], int num_students, int st_ID)
{
	Student* st = students;
	int low, high, mid;
	int round = 0;
	low = 0;
	high = num_students - 1;
	round++;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (st_ID == mid)
			return &st[mid];
		else if (st_ID < mid)
			high = mid - 1;
		else
			low = mid + 1;
		round++;
	}
	return 0;
}

void printBigArrayOfStudent_IDs(Student students[], int num_students, int num_first_last)
{
	int items_per_line = 20, num_sample_lines = 5;
	if (num_students > items_per_line * num_sample_lines)  // 배열의 크기가 items_per_line* num_sample_lines보다 크면 샘플 출력
	{
		for (int i = 0; i < items_per_line * num_sample_lines; i++)
		{
			if (i % items_per_line == 0)
				cout << "\n";

			cout.width(5);
			cout << students[i].st_id;
		}

		cout << "\n    . . . .\n";

		for (int i = num_students - items_per_line * num_sample_lines; i < num_students; i++)
		{
			if ((i - (num_students - items_per_line)) % items_per_line == 0)
				cout << "\n";

			cout.width(5);
			cout << students[i].st_id;
		}
		cout << "\n";
	}
	else  // 배열의 크기가 items_per_line* num_sample_lines보다 작으면 배열 모두 출력
	{
		for (int i = 0; i < num_students; i++)
		{
			if (i % items_per_line == 0)
				cout << "\n";

			cout.width(5);
			cout << students[i].st_id;
		}
		cout << "\n";
	}
}

void printBigArrayOfStudent_GPA_IDs(Student students[], int num_students, int num_first_last)
{
	int items_per_line = 10, num_sample_lines = 10;
	if (num_students > items_per_line * num_sample_lines)  // 배열의 크기가 items_per_line* num_sample_lines보다 크면 샘플 출력
	{
		for (int i = 0; i < items_per_line * num_sample_lines; i++)
		{
			if (i % items_per_line == 0)
				cout << "\n";

			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);
			cout << "(" << setw(5) << students[i].gpa << "," << setw(5) << students[i].st_id << ") ";
		}

		cout << "\n    . . . .\n";

		for (int i = num_students - items_per_line * num_sample_lines; i < num_students; i++)
		{
			if ((i - (num_students - items_per_line)) % items_per_line == 0)
				cout << "\n";

			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);
			cout << "(" << setw(5) << students[i].gpa << "," << setw(5) << students[i].st_id << ") ";
		}
		cout << "\n";
	}
	else  // 배열의 크기가 items_per_line* num_sample_lines보다 작으면 배열 모두 출력
	{
		for (int i = 0; i < num_students; i++)
		{
			if (i % items_per_line == 0)
				cout << "\n";

			cout.setf(ios::fixed);
			cout.setf(ios::showpoint);
			cout.precision(2);
			cout << "(" << setw(5) << students[i].gpa << "," << setw(5) << students[i].st_id << ") ";
		}
		cout << "\n";
	}
}