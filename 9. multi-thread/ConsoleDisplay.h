#pragma once

#ifndef CONSOLE_DISPLAY_H
#define CONSOLE_DISPLAY_H

#include <Windows.h>

HANDLE initConsoleHandler();  // ���� �ܼ��� �ڵ鷯�� ��ȯ�ϴ� �Լ�
void closeConsoleHandler(HANDLE hndlr);  // �ܼ� �ڵ鷯 �Ҹ�
int gotoxy(HANDLE consoleHandler, int x, int y);  // �ܼ��� (x,y)��ǥ�� Ŀ���� �̵���Ű�� �Լ�

#endif 