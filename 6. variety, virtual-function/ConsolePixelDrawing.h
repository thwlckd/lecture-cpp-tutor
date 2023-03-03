#pragma once

#ifndef PIXEL_DRAWING_H
#define PIXEL_DRAWING_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Shape.h"
#include "Color.h"

using namespace std;

/* PEN_Stypes */
#define PS_SOLID 0
#define PS_DASH 1 // -------
#define PS_DOT 2 // .......
#define PS_DASHDOT 3 // _._._._
#define PS_DASHDOTDOT 4 // _.._.._
#define PS_NULL 5
#define PS_INSIDEFRAME 6
#define PS_USERSTYLE 7
#define PS_ALTERNATE 8
#define MAX_NUM_SHAPES 100

class Shape;
class ConsolePixelFrame
{
public:
    ConsolePixelFrame(int org_x, int org_y);
    ~ConsolePixelFrame();
    void addShape(Shape* new_shape);
    void drawShapes();
    int get_pos_org_x() { return pos_org_x; }
    int get_pos_org_y() { return pos_org_y; }
    HDC getConsole_DC() { return console_DC; }
private:
    HWND console;  // 콘솔 핸들러를 값으로 가지는 변수
    HDC console_DC; // device context
    // 화면 출력 장치에 대한 시스템이 제공하는 정보를 가짐

    Shape** pShapes; // Array of Shape Pointers
    int num_shapes;  // 도형 개수
    int capacity;
    int pos_org_x;  // 콘솔 픽셀 프레임의 기준 x 좌표
    int pos_org_y;  // 콘솔 픽셀 프레임의 기준 y 좌표
    bool isValidIndex(int sub);
};
#endif