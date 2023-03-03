#include"Student.h"
#include<iomanip>

ostream& operator<< (ostream& output, const Student& s)
{
	output << "name : " << setw(7) << left << s.name << right;
	output << ", birthday : " << s.birthDate;
	output << ", st_id : " << s.st_id << ", department : " << setw(4) << s.dept_name;
	output << ", gpa : " << showpoint << fixed << setprecision(2) << s.gpa;

	return output;
}

Student::Student()
	:Person()
{
	st_id = 0;
	dept_name = "uncertain";
	gpa = 0;
}

Student::Student(string n, Date dob, int id, string dept_n, double GPA)
	:Person(n,dob)
{
	st_id = id;
	dept_name = dept_n;
	gpa = GPA;
}