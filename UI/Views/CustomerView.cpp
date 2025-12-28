#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"

#include <iostream>
#include <string>
#include <conio.h>

using std::cout;

UI::CustomerView::CustomerView()
{
    // Khởi tạo danh sách menu
    _menuOptions = {
        "Thong tin nguoi dung",
        "Danh sach tai khoan",
        "Them tai khoan",
        "Dang xuat"};

    _selectedIndex = 1; // Mặc định chọn dòng đầu tiên
}

void UI::CustomerView::render()
{
    bool running = true;
    while (running)
    {
        UI::ConsoleUtils::clearScreen();
        cout << "------NGAN HANG N06------\n\n\n";
        cout << "Chao mung khach hang: Anh \n\n\n";
        cout << "------MENU------\n\n";
        for (string option : _menuOptions)
        {
            UI::ConsoleUtils::goToXY(3, UI::ConsoleUtils::getWhereY());
            cout << option << "\n\n";
        }
        _selectedIndex = 1;
        UI::ConsoleUtils::goToXY(1, 8);
        while (running)
        {
            char key = _getch();

            if (key == 'w' || key == 'W')
            {
                if (_selectedIndex == 1)
                    continue;
                else
                {
                    UI::ConsoleUtils::goUp();
                    _selectedIndex--;
                }
            }
            else if (key == 's' || key == 'S')
            {
                if (_selectedIndex == 4)
                    continue;
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
                    showAccountListPage();
                    break;
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
        }
    }
    return;
}

// --- Các hàm giả lập chuyển trang ---
void UI::CustomerView::showUserInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- TRANG THONG TIN NGUOI DUNG ---\n";
    std::cout << "Ten: Nguyen Van A\nVIP: Khong\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAccountListPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- DANH SACH TAI KHOAN ---\n";
    std::cout << "1. 123456789 (So du: 500k)\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAddAccountPage()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "--- THEM TAI KHOAN MOI ---\n";
    std::cout << "Nhap so tai khoan muon tao: ...\n";
    std::cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::handleLogout()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "Dang dang xuat...\n";
    // Logic thoát sẽ được xử lý bởi biến running = false ở trên
}
