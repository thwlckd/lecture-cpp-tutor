#include "Circle.h"

ostream& operator<<(ostream& ostr, Circle& c)
{
	ostr << left << setw(12) << c.name << "[Cir : pos(" << c.get_pos_x() << "," << c.get_pos_y() << ")";
	ostr << "radius(" << c.radius << ")";
	ostr << ", line_color(";
	printRGB(ostr, c.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, c.brush_color);
	ostr << "), area(" << PI * c.radius * c.radius << ")]\n";
	return ostr;
}

Circle::Circle()
	:Shape()
{
	radius = 0;
}

Circle::Circle(string name)
	: Shape(name)
{
	radius = 0;
}

Circle::Circle(int px, int py, int r, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	: Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
}

Circle::~Circle()
{
	//cout << "Circle::Destructor (" << name << ").\n";
}

double Circle::getArea()
{
	double area;

	area = PI * radius * radius;

	return area;
}

void Circle::print(ostream& ostr)
{
	ostr << left << setw(12) << name << "[Cir : pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", radius(" << radius << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color); 
	ostr << "), area(" << getArea() << ")]\n";
}

void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	Ellipse(hdc, pos_center_x - radius, pos_center_y - radius, pos_center_x + radius, pos_center_y + radius);
	// 타원을 그리는 함수. 전달 인수 목록 (hdc, 좌상 x, 좌상 y, 우하 x, 우하 y)
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

Circle& Circle::operator=(const Circle& c)
{
	Shape::operator=(c);
	radius = c.radius;

	return *this;
}