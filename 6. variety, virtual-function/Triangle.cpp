#include"Triangle.h"

Triangle::Triangle()
	:Shape()
{
	base = 0;
	tri_height = 0;
}

Triangle::Triangle(string name)
	:Shape(name)
{
	base = 0;
	tri_height = 0;
}

Triangle::Triangle(int px, int py, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	base = b;
	tri_height = h;
}

Triangle::~Triangle()
{
	//cout << "Triangle::Destructor (" << name << ").\n";
}

double Triangle::getArea()
{
	double area;

	area = base * tri_height / 2;

	return area;
}

void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	POINT p[3];  // 꼭짓점 좌표 설정
	p[0].x = pos_center_x - base / 2;
	p[0].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[1].x = pos_center_x + base / 2;
	p[1].y = pos_center_y + tri_height * 1.0 / 2.0;
	p[2].x = pos_center_x;
	p[2].y = pos_center_y - tri_height * 1.0 / 2.0;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Polygon(hdc, p, 3);
	// 다각형 그리는 함수. 꼭짓점 좌표와 개수 인수로 전달
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Triangle::print(ostream& ostr)
{
	ostr << left << setw(12) << name << "[Tri : pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", base(" << base << "), " << "height(" << tri_height << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color);
	ostr << "), area(" << getArea() << ")]\n"; 
}

ostream& operator<<(ostream& ostr, Triangle& t)
{
	ostr << left << setw(12) << t.name << "[Tri : pos(" << t.get_pos_x() << "," << t.get_pos_y() << ")";
	ostr << ", base(" << t.base << "), " << "height(" << t.tri_height << ")";
	ostr << ", line_color(";
	printRGB(ostr, t.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, t.brush_color);
	ostr << "), area(" << t.base * t.tri_height / 2 << ")]\n";

	return ostr;
}

Triangle& Triangle::operator=(const Triangle& t)
{
	Shape::operator=(t);
	base = t.base;
	tri_height = t.base;

	return *this;
}