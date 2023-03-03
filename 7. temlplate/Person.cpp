#include"Person.h"

ostream& operator<< (ostream& ostr, const Person& p)
{
	ostr << "name: " << p.name;

	return ostr;
}

Person::Person()
{
}


Person::Person(string n, Date dob)
{
	name = n;
	dateOfBirth = dob;
}