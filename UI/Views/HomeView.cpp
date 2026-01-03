#include "HomeView.h"
#include "LoginView.h"
#include "RegisterView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Business/AppContext.h"
#include <iostream>
#include <vector>
#include <conio.h>

using std::cout;
using std::string;
using std::vector;

void UI::HomeView::render()
{
    vector<string> menuOptions = {
        "1. Dang Nhap",
        "2. Dang Ky",
        "3. Thoat"};
    int selectedIndex = 1;

    while (true)
    {
        UI::ConsoleUtils::clearScreen();

        // Header
        cout << "=========================================\n";
        cout << "              NGAN HANG N06              \n";
        cout << "=========================================\n\n";
        cout << "----------------- HOME ------------------\n\n";

        // Vẽ menu
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string &opt : menuOptions)
        {
            cout << "    " << opt << "\n\n";
        }

        // Vẽ mũi tên ban đầu
        UI::ConsoleUtils::goToXY(1, startY + (selectedIndex - 1) * 2);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, startY + (selectedIndex - 1) * 2);

        // Vòng lặp bắt phím điều hướng
        while (true)
        {
            char key = _getch();

            // Xóa mũi tên cũ
            UI::ConsoleUtils::goToXY(1, startY + (selectedIndex - 1) * 2);
            cout << "  ";

            if (key == 'w' || key == 'W')
            {
                if (selectedIndex > 1)
                {
                    UI::ConsoleUtils::goUp();
                    selectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (selectedIndex < (int)menuOptions.size())
                {
                    UI::ConsoleUtils::goDown();
                    selectedIndex++;
                }
            }
            else if (key == 13)
            { // Enter
                switch (selectedIndex)
                {
                case 1:
                {
                    LoginView login;
                    login.render();
                    break;
                }
                case 2:
                {
                    RegisterView reg;
                    reg.render();
                    break;
                }
                case 3:
                    UI::ConsoleUtils::clearScreen();
                    AppContext::getInstance().getBankSystem()->save();
                    return;
                }
                break; // Thoát vòng lặp phím để vẽ lại màn hình (nếu quay lại từ trang con)
            }

            // Vẽ lại mũi tên
            UI::ConsoleUtils::goToXY(1, startY + (selectedIndex - 1) * 2);
            cout << "->";
            UI::ConsoleUtils::goToXY(1, startY + (selectedIndex - 1) * 2);
        }
    }
}