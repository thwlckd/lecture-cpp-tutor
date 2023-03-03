#include"Polygon.h"

PolyGon::PolyGon()
	:Shape()
{
	radius = 0;
	num_poly = 0;
}

PolyGon::PolyGon(string name)
	:Shape(name)
{
	radius = 0;
	num_poly = 0;
}

PolyGon::PolyGon(int px, int py, int r, int n_p, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
	num_poly = n_p;
}

PolyGon::~PolyGon()
{
	//cout << "PolyGon::Destructor (" << name << ").\n";
}

void PolyGon::draw(ConsolePixelFrame cp_frame)
{
	POINT* points = (POINT*)malloc(num_poly * sizeof(POINT));  // 꼭짓점 개수만큼 POINT형 배열 동적 생성
	double rad_angle, delta_angle; // angle in radian
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	int x, y;
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();
	delta_angle = 2.0 * PI / num_poly;
	rad_angle = PI / 2.0;

	for (int i = 0; i < num_poly; i++, rad_angle += delta_angle)
	{
		// radian 값에 따라 변하는 다각형의 꼭짓점 좌표 계산
		x = pos_center_x + radius * cos(rad_angle);
		y = pos_center_y - radius * sin(rad_angle);
		points[i].x = x; points[i].y = y;
	}
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Polygon(hdc, points, num_poly);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void PolyGon::print(ostream& ostr)
{
	ostr << left << setw(12) << name << "[Poly: pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", radius(" << radius << "), " << "num_poly(" << num_poly << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color);
	ostr << ")]\n";

}

ostream& operator<<(ostream& ostr, PolyGon& p)
{
	ostr << left << setw(12) << p.name << "[Poly: pos(" << p.get_pos_x() << "," << p.get_pos_y() << ")";
	ostr << ", radius(" << p.radius << "), " << "num_poly(" << p.num_poly << ")";
	ostr << ", line_color(";
	printRGB(ostr, p.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, p.brush_color);
	ostr << ")]\n";

	return ostr;
}

PolyGon& PolyGon::operator=(PolyGon& p)
{
	Shape::operator=(p);
	radius = p.radius;
	num_poly = p.num_poly;

	return *this;
}