#pragma once

#ifndef Star_H
#define Star_H

#include <string>
#include "ConsolePixelDrawing.h"
#include "Shape.h"

using namespace std;

class Star : public Shape
{
    friend ostream& operator<<(ostream&, Star&);
public:
    Star();
    Star(string name);
    Star(int px, int py, int radius, int num_vertices, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
    //PolyGonle(PolyGonle &pg);
    ~Star();
    //double getArea();
    virtual void draw(ConsolePixelFrame cp_frame);
    //virtual void draw(); // // used for testing of late binding
    void print(ostream&);
    int getRadius() { return radius; }
    int getNumPoly() { return num_vertices; }
    Star& operator=(Star& pg);
protected:
    int radius;
    int num_vertices;  // vertex:²ÀÁþÁ¡
};
#endif