#include "RegisterView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Business/AppContext.h"
#include "../../Helper/Utils.h"
#include "../../Business/ParserFactory/ParserFactory.h" // Dùng Factory
#include "../../Business/IParsable.h"

#include <iostream>
#include <string>
#include <conio.h>

using std::cout, std::string, std::getline, std::cin;

void UI::RegisterView::render() {
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "           DANG KY TAI KHOAN             \n";
    cout << "=========================================\n\n";

    string username, pass, confirmPass, name, idCard;

    // 1. Nhập thông tin cơ bản
    cout << "Nhap Username: "; 
    getline(cin, username);


    cout << "Nhap Ho va Ten: "; 
    getline(cin, name);

    cout << "Nhap CCCD (Chi nhap so): ";
    idCard = Utils::inputNumber(12); 
    cout << "\n";

    cout << "Nhap Password: "; 
    getline(cin, pass);

    cout << "Xac nhan Password: "; 
    getline(cin, confirmPass);

    if (pass != confirmPass) {
        cout << "\n[!] Mat khau khong khop!\nNhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    // 2. Tạo Customer bằng ParserFactory
    // Giả sử format CustomerParser là: username, password, name, idCard
    try {
        ParserFactory factory;
        IParsable* parser = factory.create("Customer");
        
        if (parser) {
            string data = username + ", " + pass + ", " + name + ", " + idCard;
            auto newObj = parser->parse(data);
            auto newCust = std::static_pointer_cast<Customer>(std::shared_ptr<Object>(newObj));

            if (newCust) {
                AppContext::getInstance().getBankSystem()->addCustomer(newCust);
                cout << "\n[THANH CONG] Dang ky tai khoan thanh cong!";
                cout << "\nVui long dang nhap de su dung.";
            } else {
                 cout << "\n[LOI] Khong the tao du lieu khach hang.";
            }
        } else {
            // Fallback nếu chưa có Parser
            auto newCust = make_shared<Customer>(username, pass, name, idCard);
            AppContext::getInstance().getBankSystem()->addCustomer(newCust);
            cout << "\n[THANH CONG] Dang ky thanh cong (Direct)!";
        }
    } catch (...) {
        cout << "\n[LOI] Da xay ra loi he thong khi dang ky.";
    }

    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}