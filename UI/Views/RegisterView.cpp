#include "RegisterView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Business/AppContext.h"
#include "../../Helper/Utils.h"
#include "../../Business/ParserFactory/ParserFactory.h" // Dùng Factory
#include "../../Business/IParsable.h"
#include "../../Entity/Customer/Customer.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <memory>

using std::cout, std::string, std::getline, std::cin;

void UI::RegisterView::render()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n\n";
    cout << "----------- DANG KY TAI KHOAN -----------\n\n";

    string username, pass, confirmPass, name, phone;

    // 1. Nhập thông tin cơ bản

    cout << "Nhap Ho va Ten: ";
    getline(cin, name);

    cout << "Nhap so dien thoai: ";
    phone = Utils::inputNumberFixedLength(10);
    cout << "\n";

    cout << "Nhap Ten dang nhap: ";
    getline(cin, username);

    cout << "Nhap Mat khau: ";
    pass = Utils::inputPassword();
    cout << "\n";

    int startY = UI::ConsoleUtils::getWhereY();
    while (true)
    {
        cout << "Xac nhan Mat khau: ";
        confirmPass = Utils::inputPassword();
        cout << "\n";
        if (pass == confirmPass)
        {
            cout << "                          ";
            break;
        }
        cout << "[!] Mat khau khong khop!";
        // Xóa dòng xác nhận mật khẩu không khớp
        UI::ConsoleUtils::goToXY(0, startY);
        cout << "                   " << "                       ";
        UI::ConsoleUtils::goToXY(0, startY);
    }

    ParserFactory factory;
    IParsable *parser = factory.create("Customer");

    if (parser)
    {
        string data = phone + ", " + name + ", " + username + ", " + pass + ", " + phone;
        auto newObj = parser->parse(data);
        std::shared_ptr<Customer> newCust = std::dynamic_pointer_cast<Customer>(newObj);

        if (newCust)
        {
            AppContext::getInstance().getBankSystem()->addCustomer(newCust);
            cout << "\n[THANH CONG] Dang ky tai khoan thanh cong!";
            cout << "\nVui long dang nhap de su dung.";
        }
        else
        {
            cout << "\n[LOI] Khong the tao du lieu khach hang.";
        }
    }
    else
    {
        cout << "\nHe thong dang loi vui long thu lai sau!";
    }

    cout << "\n\nNhan phim bat ky de quay lai...";
    _getch();
}