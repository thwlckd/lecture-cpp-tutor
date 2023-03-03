#include"StudentArray.h"
#include<string>

ostream& operator<< (ostream& output, const StudentArray& sa)
{
	for (int i = 0; i < sa.num_students; i++)
		output << "Student [" << sa.students[i] << "]\n";

	return output;
}

StudentArray::StudentArray(int size)
{
	students = new Student[size];
	num_students = size;
}

StudentArray::StudentArray(const StudentArray& obj)
{
	students = new Student[obj.num_students];
	num_students = obj.num_students;
	Student(obj.students->getName(), obj.students->getBirthDate(), obj.students->st_id, obj.students->dept_name, obj.students->gpa);
}

StudentArray::~StudentArray()
{
	delete[]students;
}

Student& StudentArray::operator[](int index)
{
	if (isValidIndex(index) == false)
	{
		cout << "ERROR: Index out of range.\n";
		exit(0);
	}
	return students[index];
}

void StudentArray::sortByBirthDate()
{
	Student* pBD, * pBD_min;
	Student temp;
	int min_birthday;

	for (int i = 0; i < num_students; i++)
	{
		pBD_min = &students[i];
		min_birthday = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pBD = &students[j];
			if (pBD_min->birthDate.getElapsedDays() > pBD->birthDate.getElapsedDays())  // �� ���� ���� �߽߰�
			{
				pBD_min = pBD;  // �ش簪���� pBD_min ����
				min_birthday = j;
			}
		}
		if (min_birthday != i)
		{
			/* min_birthday �� ���� */
			temp = students[min_birthday];
			students[min_birthday] = students[i];
			students[i] = temp;
		}
	}
}

void StudentArray::sortByName()
{
	Student* pN, * pN_min;
	Student temp;
	int min_name;

	for (int i = 0; i < num_students; i++)
	{
		pN_min = &students[i];
		min_name = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pN = &students[j];
			if (pN_min->name > pN->name)  // �� ���� �̸� �߽߰�(���ĺ���)
			{
				pN_min = pN;  // �ش簪���� min_name ����
				min_name = j;
			}
		}
		if (min_name != i)
		{
			/* min_name �� ���� */
			temp = students[min_name];
			students[min_name] = students[i];
			students[i] = temp;
		}
	}
}

void StudentArray::sortByST_ID()
{
	Student* pST, * pST_min;
	Student temp;
	int min_st_id;

	for (int i = 0; i < num_students; i++)
	{
		pST_min = &students[i];
		min_st_id = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pST = &students[j];
			if (pST_min->st_id > pST->st_id)  // �� ���� �й� �߽߰�
			{
				pST_min = pST;  // �ش簪���� pST_min ����
				min_st_id = j;
			}
		}
		if (min_st_id != i)
		{
			/* min_st_id �� ���� */
			temp = students[min_st_id];
			students[min_st_id] = students[i];
			students[i] = temp;
		}
	}
}

void StudentArray::sortByGPA()
{
	Student* pGPA, * pGPA_max;
	Student temp;
	int max_gpa;

	for (int i = 0; i < num_students; i++)
	{
		pGPA_max = &students[i];
		max_gpa = i;
		for (int j = i + 1; j < num_students; j++)
		{
			pGPA = &students[j];
			if (pGPA_max->gpa < pGPA->gpa)  // �� ���� ���� �߽߰�
			{
				pGPA_max = pGPA;  // �ش簪���� max_gpa ����
				max_gpa = j;
			}
		}
		if (max_gpa != i)
		{
			/* min_gpa �� ���� */
			temp = students[max_gpa];
			students[max_gpa] = students[i];
			students[i] = temp;
		}
	}
}

bool StudentArray::isValidIndex(int index)
{
	if (index >= 0 && index < num_students)
		return true;
	else
		return false;
}