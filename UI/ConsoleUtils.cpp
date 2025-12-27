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
