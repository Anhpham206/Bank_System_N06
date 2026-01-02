#include "AccountView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Entity/Account/Account.h"

#include <iostream>
#include <string>
#include <conio.h>

using std::cout;

// Constructor khởi tạo menu và nhận số tài khoản
UI::AccountView::AccountView(shared_ptr<Account> account)
{
    _account = account;

    _menuOptions = {
        "Thong tin tai khoan",
        "Thong bao",
        "Nap tien",
        "Rut tien",
        "Chuyen tien",
        "Xoa tai khoan",
        "Quay lai"};

    _selectedIndex = 1; // Mặc định chọn dòng đầu tiên
}

void UI::AccountView::render()
{
    bool running = true;
    while (running)
    {
        UI::ConsoleUtils::clearScreen();
        cout << "------NGAN HANG N06------\n\n\n";
        // Hiển thị số tài khoản động theo dữ liệu truyền vào
        cout << "Tai khoan: " << _account->accountNumber() << "\n\n\n";
        cout << "------MENU------\n\n";

        // Vẽ danh sách menu
        for (string option : _menuOptions)
        {
            UI::ConsoleUtils::goToXY(3, UI::ConsoleUtils::getWhereY());
            cout << option << "\n\n";
        }

        _selectedIndex = 1;

        // Đặt con trỏ về vị trí lựa chọn đầu tiên (Cần căn chỉnh cho khớp với số dòng in ở trên)
        // Dựa vào CustomerView của bạn, tôi giữ nguyên logic vị trí ban đầu
        UI::ConsoleUtils::goToXY(1, 8);

        while (running)
        {
            char key = _getch();

            if (key == 'w' || key == 'W')
            {
                if (_selectedIndex == 1)
                    continue; // Chặn trên
                else
                {
                    UI::ConsoleUtils::goUp();
                    _selectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (_selectedIndex == 7) // Chặn dưới (Menu có 7 mục)
                    continue;
                else
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
                    showDepositPage();
                    break;
                case 4:
                    showWithdrawPage();
                    break;
                case 5:
                    showTransferPage();
                    break;
                case 6:
                    handleDeleteAccount();
                    // Nếu xóa thành công có thể cần logic thoát luôn, ở đây tạm thời break
                    break;
                case 7:
                    running = false; // Quay lại (Thoát vòng lặp)
                    break;
                }

                // Sau khi xử lý xong các hàm con, break khỏi switch để xóa màn hình vẽ lại
                break;
            }
        }
    }
    return;
}

// --- Các hàm giả lập chức năng (Placeholder) ---

void UI::AccountView::showAccountInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- THONG TIN TAI KHOAN: " << _account->accountNumber() << " ---\n";
    std::cout << _account->info() << "\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::showNotificationsPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- THONG BAO ---\n";
    std::cout << "- Khong co thong bao moi.\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::showDepositPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- NAP TIEN ---\n";
    std::cout << "Nhap so tien can nap: ...\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::showWithdrawPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- RUT TIEN ---\n";
    std::cout << "Nhap so tien can rut: ...\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::showTransferPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- CHUYEN TIEN ---\n";
    std::cout << "Nhap STK nguoi nhan: ...\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::AccountView::handleDeleteAccount()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- XOA TAI KHOAN ---\n";
    std::cout << "Ban co chac chan muon xoa tai khoan " << _account->accountNumber() << " khong? (Y/N)\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}
