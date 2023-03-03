#include <stdio.h>
#include "ConsoleDisplay.h"

HANDLE consoleHandler;

HANDLE initConsoleHandler()  // 현재 콘솔의 핸들러를 반환하는 함수
{
    HANDLE stdCnslHndlr;
    stdCnslHndlr = GetStdHandle(STD_OUTPUT_HANDLE);
    consoleHandler = stdCnslHndlr;
    return consoleHandler;
}

void closeConsoleHandler(HANDLE hndlr)  // 콘솔 핸들러 소멸
{
    CloseHandle(hndlr);
}

int gotoxy(HANDLE consHndlr, int x, int y)  // 콘솔의 (x,y)좌표로 커서를 이동시키는 함수
{
    if (consHndlr == INVALID_HANDLE_VALUE)
        return 0;
    COORD coords = { static_cast<short>(x), static_cast<short>(y) };
    SetConsoleCursorPosition(consHndlr, coords);
}