#include "Person.h"

void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;

	birthDate.setRandDateAttributes();  // 임의의 무작위 생년월일 생성
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;  // 이름 길이 설정
	str[0] = rand() % 26 + 'A';  // 이름 첫글자 대문자로 설정
	for (i = 1; i < name_len; i++)
		str[i] = rand() % 26 + 'a';  // 나머지 소문자로 설정
	str[i] = '\0';
	name = string(str);
}

void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);  // 왼쪽 정렬 출력
	fout << setw(16) << name;
	fout << ", birth date: ";
	fout.unsetf(ios::left);
	birthDate.fprintDate(fout);
	fout << "]";
}