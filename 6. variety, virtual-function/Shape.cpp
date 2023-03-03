#include "Shape.h"

Shape::Shape() // default constructor
{
	pos_x = pos_y = 0;
	angle = 0;
	line_color = brush_color = RGB_BLACK;
	name = "no_name";
	//cout << "Shape::Default constructor (" << name << ").\n";
}

Shape::Shape(string n)
	:name(n)
{
	pos_x = pos_y = 0;
	angle = 0;
	line_color = brush_color = RGB_BLACK;
	//cout << "Shape::Constructor (" << name << ").\n";
}

Shape::Shape(int px, int py, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string n)
{
	pos_x = px;
	pos_y = py;
	angle = ang;
	line_color = ln_clr;
	brush_color = br_clr;
	pen_thickness = pen_thick;
	name = n;
	//cout << "Shape::Constructor (" << name << ").\n";
}

Shape::~Shape()
{
	//cout << "Shape::Destructor (" << name << ").\n";
}

void Shape::draw(ConsolePixelFrame cp_frame)
{
	/* virtual function that will be late-binded to
	sub-class's draw() */
}

Shape& Shape::operator=(const Shape& s)
{
	pos_x = s.pos_x;
	pos_y = s.pos_y;
	angle = s.angle;
	name = s.name;
	line_color = s.line_color;
	brush_color = s.brush_color;

	return *this;
}

ostream& operator<<(ostream& ostr, Shape& shp)
{
	ostr << shp.name << ": pos(" << shp.get_pos_x() << ", " << shp.get_pos_y() << ")";
	ostr << ", line_color(";
	printRGB(ostr, shp.line_color);
	ostr << "), brush_color(";
	printRGB(ostr, shp.brush_color);
	ostr << ")";

	return ostr;
}

void Shape::print(ostream& ostr)
{
	ostr << name << ": pos(" << get_pos_x() << "," << get_pos_y() << ")";
	ostr << ", line_color(";
	printRGB(ostr, line_color);
	ostr << "), brush_color(";
	printRGB(ostr, brush_color);

	ostr << ")";
}