#include"Color.h"

ostream& printRGB(ostream& ostr, const COLORREF color)
{
	ostr << uppercase << hex << setfill('0');  // setfill(char a) -> 출력란의 빈 부분을 a로 채움
	ostr << "color (" << setw(6) << color << ")";

	return ostr;
}