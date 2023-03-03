#pragma once

#ifndef SHAPE_H
#define SHAPE_H

#include <string>
#include <Windows.h>
#include <conio.h>
#include "ConsolePixelDrawing.h"
#include "Color.h"

using namespace std;

#define PI 3.14159

class ConsolePixelFrame;
class Shape
{
    friend ostream& operator<<(ostream&, Shape&);
public:
    Shape(); // default constructor
    Shape(string name);
    Shape(int px, int py, double angle, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
    virtual ~Shape();
    virtual void draw(ConsolePixelFrame cp_frame);
    void print(ostream&);
    int get_pos_x() const { return pos_x; }
    int get_pos_y() const { return pos_y; }
    void set_pos_x(int x) { pos_x = x; }
    void set_pos_y(int y) { pos_y = y; }
    string getName() { return name; }
    void setName(string n) { name = n; }
    Shape& operator=(const Shape& s);
protected:
    int pos_x; // position x
    int pos_y; // position y
    double angle;
    string name;
    int pen_thickness;
    COLORREF line_color;
    COLORREF brush_color;
};
#endif