/*
*HW6_21720956_박창협
*Author : 박창협
*Programed on December. 5. 2020
*c++ 클래스의 상속, 다형성 및 가상함수를 사용하여 도형을 그리는 프로그램
*/

#include <iostream>
#include <string>
#include <fstream>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectang.h"
#include "Polygon.h"
#include "Star.h"

using namespace std;

int main()
{
	Circle cir(100, 100, 80, 0.0, RGB_BLACK, RGB_RED, 3, "Circle");
	Triangle tri(300, 100, 150, 130, 0.0, RGB_BLACK, RGB_YELLOW, 3, "Triangle");
	Rectang rec(500, 100, 150, 150, 0.0, RGB_BLACK, RGB_BLUE, 4, "Rectangle");
	PolyGon poly_5(100, 300, 80, 5, 0.0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5");
	PolyGon poly_6(300, 300, 80, 6, 0.0, RGB_BLACK, RGB_BLUE, 4, "Polygon_6");
	PolyGon poly_7(500, 300, 80, 7, 0.0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7");
    Star star_5(100, 500, 80, 5, 0.0, RGB_BLACK, RGB_GREEN, 4, "Star_5");
    ConsolePixelFrame frame(50, 50);
    frame.addShape(&cir);
    frame.addShape(&tri);
    frame.addShape(&rec);
    frame.addShape(&poly_5);
    frame.addShape(&poly_6);
    frame.addShape(&poly_7);
    frame.addShape(&star_5);
    frame.drawShapes();
    printf("hit any key to continue ....");
    _getch();
    return 0;
} // end of main()