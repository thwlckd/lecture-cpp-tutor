#pragma once

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Triangle : public Shape
{
    friend ostream& operator<<(ostream &, Triangle &);
public:
    Triangle();
    Triangle(string name);
    Triangle(int px, int py, int b, int h, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
    ~Triangle();
    double getArea();
    virtual void draw(ConsolePixelFrame cp_frame);
    void print(ostream&);
    int getBase() { return base; }
    int getHeight() { return tri_height; }
    Triangle& operator=(const Triangle& tri);
protected:
    int base;
    int tri_height;
};
#endif