#include"Color.h"

ostream& printRGB(ostream& ostr, const COLORREF color)
{
	ostr << uppercase << hex << setfill('0');  // setfill(char a) -> ��¶��� �� �κ��� a�� ä��
	ostr << "color (" << setw(6) << color << ")";

	return ostr;
}