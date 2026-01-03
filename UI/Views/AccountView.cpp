#include "AccountView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Entity/Account/Account.h"
#include "../../Entity/Customer/Customer.h"
#include "TransferView.h"
#include "DepositView.h"
#include "WithdrawView.h"
#include "../../Entity/Command/ShowNotificationsCmd.h"
#include "../../Business/AppContext.h"
#include "../../Helper/Utils.h"
#include "WithdrawView.h"
#include "DepositView.h"

#include <iostream>
#include <string>
#include <conio.h>

using std::cout;

// Constructor khởi tạo menu và nhận số tài khoản
UI::AccountView::AccountView(shared_ptr<Account> account)
{
    _account = account;

    _menuOptions = {
        "1. Thong tin tai khoan",
        "2. Thong bao",
        "3. Nap tien",
        "4. Rut tien",
        "5. Chuyen tien",
        "6. Xoa tai khoan",
        "Quay lai"};

    _selectedIndex = 1; // Mặc định chọn dòng đầu tiên
}

void UI::AccountView::render()
{
    bool running = true;
    while (running)
    {
        UI::ConsoleUtils::clearScreen();
        cout << "=========================================\n";
        cout << "              NGAN HANG N06              \n";
        cout << "=========================================\n";
        // Hiển thị số tài khoản động theo dữ liệu truyền vào
        cout << "Tai khoan: " << _account->accountNumber() << "\n\n";
        cout << "------------------ MENU -----------------\n\n";

        // Vẽ danh sách menu
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string &option : _menuOptions)
        {
            cout << "    " << option << "\n\n";
        }
        UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2); // Đưa con trỏ về lại đầu dòng

        while (running)
        {
            char key = _getch();

            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
            cout << "   ";

            if (key == 'w' || key == 'W')
            {
                if (_selectedIndex > 1)
                {
                    UI::ConsoleUtils::goUp();
                    _selectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (_selectedIndex < (int)_menuOptions.size())
                {
                    UI::ConsoleUtils::goDown();
                    _selectedIndex++;
                }
            }
            else if (key == 13) // Enter
            {
                switch (_selectedIndex)
                {
                case 1:
                    showAccountInfoPage();
                    break;
                case 2:
                    showNotificationsPage();
                    break;
                case 3:
                {
                    DepositView depositView(_account);
                    depositView.render();
                    break;
                }
                case 4:
                {
                    WithdrawView withdrawView(_account);
                    withdrawView.render();
                    break;
                }
                case 5:
                {
                    TransferView transferView(_account);
                    transferView.render();
                    break;
                }

                case 6:
                    handleDeleteAccount();
                    running = false; // Sau khi xóa tài khoản, thoát luôn về menu chính
                    break;
                case 7:
                    running = false; // Quay lại (Thoát vòng lặp)
                    break;
                }

                // Sau khi xử lý xong, break để vẽ lại toàn bộ màn hình
                break;
            }

            // Vẽ lại mũi tên ở vị trí mới
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
            cout << "->";
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
        }
    }
    return;
}

// --- Các hàm giả lập chức năng (Placeholder) ---

void UI::AccountView::showAccountInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "=========================================\n";
    std::cout << "              NGAN HANG N06              \n";
    std::cout << "=========================================\n\n";
    std::cout << "---------- THONG TIN TAI KHOAN ----------\n\n";
    std::cout << _account->info() << "\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::showNotificationsPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "=========================================\n";
    std::cout << "              NGAN HANG N06              \n";
    std::cout << "=========================================\n\n";
    std::cout << "--------------- THONG BAO ---------------\n\n";

    ShowNotificationsCmd cmd(_account);
    bool has = cmd.execute();

    std::cout << "\n";

    // Draw the "Quay lai" button on its own line and place an arrow to select it
    int btnY = UI::ConsoleUtils::getWhereY();

    std::cout << "    Quay lai";
    UI::ConsoleUtils::goToXY(1, btnY);
    std::cout << "->";
    UI::ConsoleUtils::goToXY(1, btnY);

    // Wait for Enter to return
    while (true)
    {
        char key = _getch();
        if (key == 13)
            break;
    }
}

void UI::AccountView::handleDeleteAccount()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "=========================================" << "\n";
    std::cout << "              NGAN HANG N06              " << "\n";
    std::cout << "=========================================" << "\n\n";
    std::cout << "------------- XOA TAI KHOAN -------------\n\n";
    std::cout << "Ban co chac chan muon xoa tai khoan " << _account->accountNumber() << "? (Y/N)\n";

    // Confirm
    char c = _getch();
    if (c != 'Y' && c != 'y')
    {
        std::cout << "\nHuy thao tac. Nhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    // Ask for PIN (up to 3 attempts)
    int attempts = 0;
    int startY = UI::ConsoleUtils::getWhereY();
    while (attempts < 3)
    {
        std::cout << "\nNhap ma PIN: ";
        std::string pin = Utils::inputNumberFixedLength(6);
        std::cout << "\n";

        if (_account->verifyPIN(pin))
        {
            // Remove account from bank system and owner
            auto bank = AppContext::getInstance().getBankSystem();
            auto owner = bank->getCustomer(_account->owner());
            if (owner)
            {
                owner->removeAccount(_account->accountNumber());
            }
            bank->removeAccount(_account->accountNumber());

            std::cout << "\n[X] Xoa tai khoan thanh cong!          \n\n";
            std::cout << "Nhan phim bat ky de quay lai...";
            _getch();
            return;
        }
        else
        {
            attempts++;
            if (attempts >= 3)
            {
                std::cout << "\n[!] Nhap sai qua 3 lan. Thao tac bi huy.\n";
                std::cout << "Nhan phim bat ky de quay lai...";
                _getch();
                return;
            }
            std::cout << "\n[!] Sai ma PIN! Vui long thu lai.\n";
            UI::ConsoleUtils::goToXY(0, startY + 1);
            std::cout << "                       ";
            UI::ConsoleUtils::goToXY(0, startY + 1);
        }
    }
}
