#include "ConsoleUtils.h"
#include <windows.h>

void UI::ConsoleUtils::goToXY(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void UI::ConsoleUtils::clearScreen()
{
    system("cls");
}

int UI::ConsoleUtils::getWhereX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.X;
    return 0;
}

int UI::ConsoleUtils::getWhereY()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        return csbi.dwCursorPosition.Y;
    return 0;
}

void UI::ConsoleUtils::goUp()
{
    int x = getWhereX();
    int y = getWhereY();
    y -= 2;
    goToXY(x, y);
}

void UI::ConsoleUtils::goDown()
{
    int x = getWhereX();
    int y = getWhereY();
    y += 2;
    goToXY(x, y);
}
