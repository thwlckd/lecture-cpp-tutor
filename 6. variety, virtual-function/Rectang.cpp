#include"Rectang.h"

Rectang::Rectang()
	:Shape()
{
	width = 0;
	length = 0;
}

Rectang::Rectang(string name)
	:Shape(name)
{
	width = 0;
	length = 0;
}

Rectang::Rectang(int px, int py, int w, int l, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, ln_clr, br_clr, pen_thick, name)
{
	width = w;
	length = l;
}

Rectang::~Rectang()
{
	//cout << "Rectang::Destructor (" << name << ").\n";
}

double Rectang::getArea()
{
	double area;

	area = width * length;

	return area;
}

void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int pos_center_x, pos_center_y;

	pos_center_x = cp_frame.get_pos_org_x() + get_pos_x();
	pos_center_y = cp_frame.get_pos_org_y() + get_pos_y();
	POINT p[4];  // p : »ç°¢Çü ²ÀÁþÁ¡ ÁÂÇ¥
	p[0].x = pos_center_x - width / 2;
	p[0].y = pos_center_y - length / 2;
	p[1].x = pos_center_x + width / 2;
	p[1].y = pos_center_y - length / 2.0;
	p[2].x = pos_center_x + width / 2;
	p[2].y = pos_center_y + length / 2.0;
	p[3].x = pos_center_x - width / 2;
	p[3].y = pos_center_y + length / 2.0;

	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, line_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Polygon(hdc, p, 4);
	// ´Ù°¢Çü ±×¸®´Â ÇÔ¼ö. parameter(handler for device console, ²ÀÁþÁ¡ ÁÂÇ¥, ²ÀÁþÁ¡ °³¼ö)
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Rectang::print(ostream& ostr)
{
	ostr << left << setw(12) << name << "[Rec : pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", width(" << width << "), " << "height(" << length << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color);
	ostr << "), area(" << getArea() << ")]\n";

}

ostream& operator<<(ostream& ostr, Rectang& r)
{
	ostr << left << setw(12) << r.name << "[Rec : pos(" << r.get_pos_x() << "," << r.get_pos_y() << ")";
	ostr << ", width(" << r.width << "), " << "), height(" << r.length << ")";
	ostr << ", line_color(";
	printRGB(ostr, r.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, r.brush_color);
	ostr << "), area(" << r.width * r.length / 2 << ")]\n";

	return ostr;
}

Rectang& Rectang::operator=(Rectang& r)
{
	Shape::operator=(r);
	width = r.width;
	length = r.length;

	return *this;
}