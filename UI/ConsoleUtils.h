#ifndef CONSOLE_UTILS_H
#define CONSOLE_UTILS_H

namespace UI
{
    class ConsoleUtils
    {
    public:
        static void goToXY(int x, int y);
        static void clearScreen();
        static int getWhereX(); // lay toa do x hien tai
        static int getWhereY(); // lay toa do y hien tai
        static void goUp();     // di chuyen con tro len tren
        static void goDown();   // di chuyen con tro xuong duoi
    };
}

#endif