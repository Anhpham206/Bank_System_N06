#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"
#include "AccountView.h"
#include "../../Helper/Utils.h"

// 1. Include các module hệ thống
#include "../../Business/AppContext.h"
// #include "../../Entity/BankSystem/BankSystem.h"
#include "../../Entity/Customer/Customer.h"
// #include "../../Entity/Account/CheckingAccount.h" // Dùng để tạo tài khoản mới
// #include "../../Entity/Account/SavingAccount.h"   // Dùng để tạo tài khoản mới

// 2. Include các Command
#include "../../Entity/Command/LogoutCmd.h"

// 3. Include các Transaction

#include "../../Business/ParserFactory/ParserFactory.h"
#include "../../Business/IParsable.h"

#include <iostream>
#include <conio.h>
#include <iomanip>
#include <vector>

using std::cout;
using std::vector;

UI::CustomerView::CustomerView()
{
    // Khởi tạo danh sách menu 8 chức năng
    _menuOptions = {
        "1. Thong tin nguoi dung",
        "2. Danh sach tai khoan",
        "3. Them tai khoan moi",
        "4. Dang xuat"};
    _bankSystem = AppContext::getInstance().getBankSystem();
    _currentCustomer = _bankSystem->currentCustomer();
    _selectedIndex = 1; // Mặc định chọn dòng đầu tiên
}

void UI::CustomerView::render()
{
    bool running = true;
    while (running)
    {
        UI::ConsoleUtils::clearScreen();

        // Lấy thông tin khách hàng hiện tại từ Context
        auto bank = AppContext::getInstance().getBankSystem();
        auto cust = bank->currentCustomer();
        string name = (cust) ? cust->getName() : "Khach";

        // Header
        cout << "=========================================\n";
        cout << "              NGAN HANG N06              \n";
        cout << "=========================================\n";
        cout << "Xin chao: " << name << "\n\n\n";
        cout << "----------------- MENU ------------------\n\n";
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string &option : _menuOptions)
        {
            cout << "    " << option << "\n\n";
        }
        UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2); // Đưa con trỏ về lại đầu dòng

        while (true)
        {
            char key = _getch(); // Nhận phím

            // Xóa mũi tên ở vị trí cũ
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
            cout << "   ";

            if (key == 'w' || key == 'W')
            {
                if (_selectedIndex == 1)
                {
                }

                else
                {
                    UI::ConsoleUtils::goUp();
                    _selectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (_selectedIndex == 4)
                {
                }
                else
                {
                    UI::ConsoleUtils::goDown();
                    _selectedIndex++;
                }
            }
            else if (key == 13)
            { // 13 là mã ASCII của phím Enter
                // Xử lý chọn dựa trên index hiện tại
                switch (_selectedIndex)
                {
                case 1:
                    showUserInfoPage();
                    break;
                case 2:
                {
                    showAccountListPage();
                    break;
                }
                case 3:
                    showAddAccountPage();
                    break;
                case 4:
                    handleLogout();
                    running = false; // Thoát vòng lặp
                    break;
                }
                break;
                // Nếu chưa thoát, xóa màn hình để vẽ lại cho sạch (nếu trang con đã in gì đó)
            }
            UI::ConsoleUtils::goToXY(1, UI::ConsoleUtils::getWhereY());
            cout << "->";
            UI::ConsoleUtils::goToXY(1, UI::ConsoleUtils::getWhereY());
        }
    }
}

void UI::CustomerView::showUserInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    auto cust = AppContext::getInstance().getBankSystem()->currentCustomer();

    cout << "--- THONG TIN CA NHAN ---\n\n";
    if (cust)
    {
        cout << cust->info() << "\n\n";
    }
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAccountListPage()
{
    bool staying = true;

    while (staying)
    {
        UI::ConsoleUtils::clearScreen();

        int localSelectedIndex = 1;

        std::vector<string> accountsNumber = _currentCustomer->getOwnedAccountIds();
        vector<string> currentOptions = accountsNumber;

        currentOptions.push_back("Quay lai"); // Thêm lựa chọn thoát vào cuối

        // Header
        cout << "=========================================\n";
        cout << "           DANH SACH TAI KHOAN           \n";
        cout << "=========================================\n";
        cout << "Chon tai khoan de thao tac:\n\n\n";

        if (currentOptions.size() == 1)
        {
            cout << "    Quy khach hien chua co tai khoan!\n\n";
            cout << "    Quay lai";
            UI::ConsoleUtils::goToXY(1, UI::ConsoleUtils::getWhereY());
            cout << "->";
            UI::ConsoleUtils::goToXY(1, UI::ConsoleUtils::getWhereY());
            char key = ' ';
            while (key != 13)
            {
                key = _getch();
            }
            return;
        }

        // 3. In danh sách ra màn hình
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string &opt : currentOptions)
        {
            if (opt == "Quay lai")
                cout << "    " << opt;
            else
                cout << "    Tai khoan: " << opt << " - " << _bankSystem->getAccount(opt)->type() << "\n\n";
        }

        // Vẽ mũi tên ban đầu
        UI::ConsoleUtils::goToXY(1, startY + (localSelectedIndex - 1) * 2);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, startY + (localSelectedIndex - 1) * 2); // Đưa con trỏ về lại

        while (staying)
        {
            char key = _getch();

            // UI::ConsoleUtils::goToXY(1, startY + (localSelectedIndex - 1) * 2);
            cout << "  ";

            if (key == 'w' || key == 'W')
            {
                if (localSelectedIndex == 1)
                {
                }
                else
                {
                    UI::ConsoleUtils::goUp();
                    localSelectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (localSelectedIndex == currentOptions.size())
                {
                }
                else
                {
                    UI::ConsoleUtils::goDown();
                    localSelectedIndex++;
                }
            }
            else if (key == 13) // Enter
            {

                if (localSelectedIndex == currentOptions.size())
                {
                    staying = false;
                }
                else
                {
                    string selectedAccNum = accountsNumber[localSelectedIndex - 1];

                    auto accPtr = _bankSystem->getAccount(selectedAccNum);

                    if (accPtr)
                    {
                        // Mở AccountView
                        UI::AccountView accountView(accPtr);
                        accountView.render();
                    }
                }
                break;
            }

            UI::ConsoleUtils::goToXY(1, startY + (localSelectedIndex - 1) * 2);
            cout << "->";
            UI::ConsoleUtils::goToXY(1, startY + (localSelectedIndex - 1) * 2);
        }
    }
}

void UI::CustomerView::showAddAccountPage()
{
    // 1. Cấu hình Menu chọn loại tài khoản
    vector<string> accountTypes = {
        "1. Checking Account (Tai khoan thanh toan)",
        "2. Saving Account (Tai khoan tiet kiem)",
        "3. Quay lai"};

    int localIndex = 1; // Biến index cục bộ cho menu này
    bool selectingType = true;

    while (selectingType)
    {
        UI::ConsoleUtils::clearScreen();
        cout << "=========================================\n";
        cout << "              NGAN HANG N06              \n";
        cout << "=========================================\n\n";
        cout << "-------------- MO TAI KHOAN -------------\n\n";
        cout << "Chon loai tai khoan:\n\n";

        // In danh sách lựa chọn
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string &opt : accountTypes)
        {
            cout << "    " << opt << "\n\n";
        }

        // Vẽ mũi tên ban đầu
        UI::ConsoleUtils::goToXY(1, startY + (localIndex - 1) * 2);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, startY + (localIndex - 1) * 2);

        // Vòng lặp bắt phím (Logic giống hệt render)
        while (true)
        {
            char key = _getch();

            // Xóa mũi tên cũ
            UI::ConsoleUtils::goToXY(1, startY + (localIndex - 1) * 2);
            cout << "  ";

            if (key == 'w' || key == 'W')
            {
                if (localIndex > 1)
                {
                    UI::ConsoleUtils::goUp();
                    localIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (localIndex < (int)accountTypes.size())
                {
                    UI::ConsoleUtils::goDown();
                    localIndex++;
                }
            }
            else if (key == 13) // Enter
            {
                // Xử lý lựa chọn
                if (localIndex == 3) // Quay lại
                {
                    return;
                }

                // Nếu chọn 1 hoặc 2, thoát vòng lặp menu để sang màn hình nhập liệu
                selectingType = false;
                break;
            }

            // Vẽ lại mũi tên ở vị trí mới
            UI::ConsoleUtils::goToXY(1, startY + (localIndex - 1) * 2);
            cout << "->";
            UI::ConsoleUtils::goToXY(1, startY + (localIndex - 1) * 2);
        }
    }

    // ---------------------------------------------------------
    // PHẦN 2: MÀN HÌNH NHẬP THÔNG TIN (Sau khi đã chọn loại)
    // ---------------------------------------------------------

    UI::ConsoleUtils::clearScreen();
    string accTypeStr = (localIndex == 1) ? "CHECKING ACCOUNT" : "SAVING ACCOUNT";
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n\n";

    cout << "---------- TAO " << accTypeStr << " ----------\n\n";

    // Nhập Số tài khoản
    cout << "Nhap so tai khoan moi (10 so): ";
    string accNum = Utils::inputNumber(10);
    cout << "\n";
    // Kiểm tra trùng lặp
    if (_bankSystem->getAccount(accNum) != nullptr)
    {
        cout << "\n[!] LOI: So tai khoan da ton tai!\nNhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    // Nhập PIN
    cout << "Nhap ma PIN (6 so): ";
    string pin = Utils::inputNumber(6);
    cout << "\n";
    // Nhập số dư ban đầu
    cout << "Nhap so du ban dau: ";
    string initBalance = Utils::inputNumber(15);
    cout << "\n";
    shared_ptr<Account> newAccount = nullptr;
    string ownerUsername = _currentCustomer->username();
    ParserFactory factory;
    string data = accNum + ", " + ownerUsername + ", " + initBalance + ", " + pin;

    // Tạo object dựa trên lựa chọn menu trước đó
    if (localIndex == 1)
    {
        IParsable *parser = factory.create("CheckingAccount");
        newAccount = std::static_pointer_cast<Account>(parser->parse(data));
    }
    else
    {
        data += ", 0.05";
        IParsable *parser = factory.create("SavingAccount");
        newAccount = std::static_pointer_cast<Account>(parser->parse(data));
    }

    // Lưu vào hệ thống
    if (newAccount)
    {
        _currentCustomer->addAccount(newAccount);

        cout << "\n[THANH CONG] Da tao tai khoan moi!\n";
        cout << "So TK: " << accNum << "\n";
        cout << "Loai: " << accTypeStr << "\n";
    }
    else
    {
        cout << "\n[LOI] Khong the tao tai khoan.\n";
    }

    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::handleLogout()
{
    UI::ConsoleUtils::clearScreen();
    cout << "Dang dang xuat...\n";
    _currentCustomer = nullptr;
    LogoutCmd logOut;
    logOut.execute();
    // Logic thoát sẽ được xử lý bởi biến running = false ở trên
}
