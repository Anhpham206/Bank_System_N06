#include <iostream>
#include <string>
#include <memory>
#include <conio.h>
#include <windows.h> // Để dùng SetConsoleOutputCP nếu cần tiếng Việt

// Include các module
#include "Business/AppContext.h"
#include "Entity/BankSystem/BankSystem.h"
#include "UI/Views/HomeView.h"
#include "UI/Utils/ConsoleUtils.h"

using namespace std;

int main()
{
    // Hỗ trợ hiển thị tiếng Việt (nếu cần)
    SetConsoleOutputCP(65001);

    // 1. Khởi tạo hệ thống
    AppContext::getInstance().initialize("NGAN HANG N06");
    auto bank = AppContext::getInstance().getBankSystem();

    bank->run();

    UI::HomeView homeView;
    homeView.render();
    return 0;
}