#include "LoginView.h"
#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Business/AppContext.h"
#include <iostream>
#include <conio.h>

using std::cout, std::string, std::getline, std::cin;

void UI::LoginView::render() {
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              DANG NHAP                  \n";
    cout << "=========================================\n\n";

    string username, password;

    cout << "Username: "; 
    getline(cin, username);

    cout << "Password: "; 
    getline(cin, password);

    auto bank = AppContext::getInstance().getBankSystem();
    if (bank->login(username, password)) {
        cout << "\n>> Dang nhap thanh cong!\n";
        cout << "Nhan phim bat ky de vao he thong...";
        _getch();

        // Chuyển sang CustomerView
        CustomerView custView; // Constructor CustomerView đã tự lấy user hiện tại từ AppContext
        custView.render();
    } else {
        cout << "\n[!] Sai Username hoac Password!\n";
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
    }
}