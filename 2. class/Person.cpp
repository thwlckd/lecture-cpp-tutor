#include "Person.h"

void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;

	birthDate.setRandDateAttributes();  // ������ ������ ������� ����
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;  // �̸� ���� ����
	str[0] = rand() % 26 + 'A';  // �̸� ù���� �빮�ڷ� ����
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a';  // ������ �ҹ��ڷ� ����
	str[i] = '\0';
	name = string(str);
}

void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);  // ���� ���� ���
	fout << setw(16) << name;
	fout << ", birth date: ";
	fout.unsetf(ios::left);
	birthDate.fprintDate(fout);
	fout << "]";
}