#include <iostream>
#include <string>
#include <memory>
#include <conio.h>
#include <windows.h> // Để dùng SetConsoleOutputCP nếu cần tiếng Việt

// Include các module
#include "Business/AppContext.h"
#include "Entity/BankSystem/BankSystem.h"
#include "UI/Views/CustomerView.h"
#include "UI/Utils/ConsoleUtils.h"

using namespace std;

void showLoginScreen()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=======================================\n";
    cout << "      HE THONG QUAN LY NGAN HANG       \n";
    cout << "=======================================\n\n";
}

int main()
{
    // Hỗ trợ hiển thị tiếng Việt (nếu cần)
    SetConsoleOutputCP(65001);

    // 1. Khởi tạo hệ thống
    AppContext::getInstance().initialize("NGAN HANG N06");
    auto bank = AppContext::getInstance().getBankSystem();

    // 2. NẠP DỮ LIỆU TỪ FILE
    // Hàm này sẽ tự động đọc Data/Customers và Data/Accounts
    cout << "Dang khoi tao du lieu tu file...\n";
    try
    {
        bank->run();
        cout << "[OK] Da nap du lieu thanh cong.\n";
    }
    catch (const std::exception &e)
    {
        cout << "[LOI] Khong the doc file du lieu: " << e.what() << "\n";
        cout << "Vui long kiem tra lai thu muc Data.\n";
        system("pause");
        return 1;
    }
    Sleep(10000); // Dừng 1 chút để user thấy thông báo

    // 3. Vòng lặp đăng nhập
    bool appRunning = true;
    while (appRunning)
    {
        showLoginScreen();

        string username, password;
        cout << "--- DANG NHAP ---\n";
        cout << "(Go 'exit' de thoat chuong trinh)\n\n";

        cout << "Username: ";
        cin >> username;
        if (username == "exit")
        {
            appRunning = false;
            break;
        }

        cout << "Password: ";
        cin >> password;

        // Xử lý đăng nhập
        if (bank->login(username, password))
        {
            // Đăng nhập thành công -> Vào màn hình chính CustomerView
            UI::CustomerView view;
            view.render();
        }
        else
        {
            cout << "\nDang nhap that bai! Nhan phim bat ky de thu lai...";
            _getch();
        }
    }

    cout << "\nTam biet quy khach!\n";
    return 0;
}