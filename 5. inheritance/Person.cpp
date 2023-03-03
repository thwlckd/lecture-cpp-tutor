#include "Person.h"

ostream& operator<< (ostream& output, const Person& p)
{
	output << "Person name : " << p.name << "\nPerson birthday : " << p.birthDate;

	return output;
}

Person::Person()
{
	name = "Hong Gil-Dong";
	Date();
}

Person::Person(string n, Date bd)
{
	name = n;
	Date(bd.getYear(), bd.getMonth(), bd.getDay());
}
