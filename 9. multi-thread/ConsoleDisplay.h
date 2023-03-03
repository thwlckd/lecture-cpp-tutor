#pragma once

#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();  // 현재 콘솔의 핸들러를 반환하는 함수
void closeConsoleHandler(HANDLE hndlr);  // 콘솔 핸들러 소멸
int gotoxy(HANDLE consoleHandler, int x, int y);  // 콘솔의 (x,y)좌표로 커서를 이동시키는 함수

#endif 