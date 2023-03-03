#include"Student.h"

ostream& operator<< (ostream& ostr, const Student& st)
{
	ostr << "Student [ " << "st_id: " << st.st_id << ", name: " << setw(10) << left;
	ostr << st.name << ", arrival: " << st.arrivalTime << ", gpa: " << st.gpa << "]";

	return ostr;
}

Student::Student()
	:Person()
{
	st_id = 0;
	gpa = 0;
}

Student::Student(int id, string n, Date dob, Time avt, double gp)
	: Person(n, dob)
{
	st_id = id;
	gpa = gp;
	arrivalTime = avt;
}