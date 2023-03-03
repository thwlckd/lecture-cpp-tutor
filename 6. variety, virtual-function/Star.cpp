#include"Star.h"

Star::Star()
	:Shape()
{
	radius = 0;
	num_vertices = 0;
}

Star::Star(string name)
	:Shape(name)
{
	radius = 0;
	num_vertices = 0;
}

Star::Star(int px, int py, int r, int n_v, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	radius = r;
	num_vertices = n_v;
}

Star::~Star()
{
	//cout << "Star::Destructor (" << name << ").\n";
}

void Star::draw(ConsolePixelFrame cp_frame)
{
	POINT* points = (POINT*)malloc(5.0 * sizeof(POINT));  // 크기가 5인 POINT 배열 생성
	double rad_angle, delta_angle;  // angle in radian
	int pos_center_x, pos_center_y;
	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	int x, y;
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();
	delta_angle = 2.0 * PI / 5.0;
	rad_angle = PI / 2.0;

	for (int i = 0; i < 5.0; i++, rad_angle += delta_angle)
	{
		// radian 값에 따라 변하는 별의 꼭짓점 좌표 계산
		x = pos_center_x + radius * cos(rad_angle);
		y = pos_center_y - radius * sin(rad_angle);
		points[i].x = x;
		points[i].y = y;
	}
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);

	//instead of Polygon(hdc, points, num_poly);
	MoveToEx(hdc, points[0].x, points[0].y, NULL);  // point[0]로 좌표 이동
	LineTo(hdc, points[2].x, points[2].y);  // 기존 좌표(point[0])와 인수로 받은 좌표(point[2]) 연결
	LineTo(hdc, points[4].x, points[4].y);
	LineTo(hdc, points[1].x, points[1].y);
	LineTo(hdc, points[3].x, points[3].y);
	LineTo(hdc, points[0].x, points[0].y);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Star::print(ostream& ostr)
{
	ostr << left << setw(12) << name << "[Poly: pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", radius(" << radius << "), " << "num_vertices(" << num_vertices << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color);
	ostr << ")]\n";
}

ostream& operator<<(ostream& ostr, Star& s)
{
	ostr << left << setw(12) << s.name << "[Poly: pos(" << s.get_pos_x() << "," << s.get_pos_y() << ")";
	ostr << ", radius(" << s.radius << "), " << "num_vertices(" << s.num_vertices << ")";
	ostr << ", line_color(";
	printRGB(ostr, s.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, s.brush_color);
	ostr << ")]\n";

	return ostr;
}

Star& Star::operator=(Star& s)
{
	Shape::operator=(s);
	radius = s.radius;
	num_vertices = s.num_vertices;

	return *this;
}