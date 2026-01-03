#include "LoginView.h"
#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Helper/Utils.h"
#include "../../Entity/Command/LoginCmd.h"
#include <iostream>
#include <conio.h>

using std::cout, std::string, std::getline, std::cin;

void UI::LoginView::render()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n";
    cout << "--------------- DANG NHAP ---------------\n\n";

    string username, password;

    cout << "Username: ";
    getline(cin, username);

    cout << "Password: ";
    password = Utils::inputPassword();
    cout << "\n";
    LoginCmd loginCmd(username, password);
    if (loginCmd.execute())
    {

        // Chuyển sang CustomerView
        CustomerView custView; // Constructor CustomerView đã tự lấy user hiện tại từ AppContext
        custView.render();
    }
    else
    {
        cout << "\n[!] Sai Username hoac Password!\n";
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
    }
}