#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"
#include "AccountView.h"

// 1. Include các module hệ thống
#include "../../Business/AppContext.h"
#include "../../Entity/BankSystem/BankSystem.h"
#include "../../Entity/Customer/Customer.h"
#include "../../Entity/Account/CheckingAccount.h" // Dùng để tạo tài khoản mới

// 2. Include các Command
#include "../../Entity/Command/DepositCmd.h"
#include "../../Entity/Command/WithdrawCmd.h"
#include "../../Entity/Command/TransferCmd.h"
#include "../../Entity/Command/ShowNotificationsCmd.h"
#include "../../Entity/Command/LogoutCmd.h"

// 3. Include các Transaction
#include "../../Entity/Transaction/DepositTransaction.h"
#include "../../Entity/Transaction/WithdrawTransaction.h"
#include "../../Entity/Transaction/TransferTransaction.h"

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
        cout << "--------------- MENU --------------------\n\n";
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
                    // showAddAccountPage();
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

// void UI::CustomerView::showAddAccountPage()
// {
//     UI::ConsoleUtils::clearScreen();
//     cout << "--- MO TAI KHOAN MOI ---\n\n";

//     auto bank = AppContext::getInstance().getBankSystem();
//     auto cust = bank->currentCustomer();

//     if (!cust)
//         return;

//     string newAccNum, pin;
//     long long initBal;

//     cout << "Nhap so tai khoan muon tao (VD: 123456): ";
//     cin >> newAccNum;

//     // Kiểm tra trùng lặp trong toàn hệ thống ngân hàng
//     if (bank->getAccount(newAccNum) != nullptr)
//     {
//         cout << "\n[!] LOI: So tai khoan nay da ton tai. Vui long chon so khac.\n";
//         cout << "Nhan phim bat ky de quay lai...";
//         _getch();
//         return;
//     }

//     cout << "Nhap ma PIN (mat khau giao dich): ";
//     cin >> pin;
//     cout << "Nhap so du ban dau (VND): ";
//     cin >> initBal;

//     // Tạo tài khoản CheckingAccount
//     auto newAcc = make_shared<CheckingAccount>(newAccNum, cust->getName(), initBal, pin);

//     // Thêm vào Customer (Hàm này sẽ tự gọi bank->addAccount)
//     cust->addAccount(newAcc);

//     cout << "\n[OK] Mo tai khoan thanh cong!\n";
//     cout << "So tai khoan: " << newAccNum << endl;
//     cout << "So du: " << initBal << " VND\n";

//     cout << "\nNhan phim bat ky de quay lai...";
//     _getch();
// }

// void UI::CustomerView::handleDeposit()
// {
//     UI::ConsoleUtils::clearScreen();
//     cout << "--- NAP TIEN ---\n\n";

//     // 1. Nhập tài khoản nguồn (của mình)
//     auto acc = inputOwnedAccount("Nhap so tai khoan nhan tien: ");
//     if (!acc)
//     {
//         _getch();
//         return;
//     }

//     // 2. Nhập số tiền
//     long long amount;
//     cout << "Nhap so tien muon nap: ";
//     cin >> amount;

//     // 3. Tạo Transaction & Command
//     auto trans = make_shared<DepositTransaction>(acc, amount);
//     DepositCmd cmd(trans);

//     // 4. Thực thi
//     cmd.execute();

//     // In kết quả (Transaction tự cập nhật số dư, ta chỉ cần in ra)
//     cout << "\n[OK] Giao dich hoan tat.\n";
//     cout << "So du moi: " << acc->balance() << " VND\n";

//     cout << "\nNhan phim bat ky de quay lai...";
//     _getch();
// }

// void UI::CustomerView::handleWithdraw()
// {
//     UI::ConsoleUtils::clearScreen();
//     cout << "--- RUT TIEN ---\n\n";

//     auto acc = inputOwnedAccount("Nhap so tai khoan rut tien: ");
//     if (!acc)
//     {
//         _getch();
//         return;
//     }

//     long long amount;
//     cout << "Nhap so tien muon rut: ";
//     cin >> amount;

//     string pin;
//     cout << "Nhap ma PIN: ";
//     cin >> pin;

//     // Tạo Transaction Rút tiền
//     auto trans = make_shared<WithdrawTransaction>(acc, amount, pin);
//     WithdrawCmd cmd(trans);

//     // Thực thi (Logic kiểm tra PIN và Số dư nằm trong Transaction::execute)
//     cout << "\nDang xu ly...\n";
//     cmd.execute();

//     cout << "\n(Ket thuc giao dich)";
//     cout << "\nNhan phim bat ky de quay lai...";
//     _getch();
// }

// void UI::CustomerView::handleTransfer()
// {
//     UI::ConsoleUtils::clearScreen();
//     cout << "--- CHUYEN KHOAN ---\n\n";

//     // 1. Tài khoản nguồn (Của mình)
//     auto srcAcc = inputOwnedAccount("TK Nguon (Cua ban): ");
//     if (!srcAcc)
//     {
//         _getch();
//         return;
//     }

//     // 2. Tài khoản đích (Của bất kỳ ai trong hệ thống)
//     string destId;
//     cout << "TK Nhan (Nguoi khac): ";
//     cin >> destId;

//     auto bank = AppContext::getInstance().getBankSystem();
//     auto destAcc = bank->getAccount(destId);

//     if (!destAcc)
//     {
//         cout << "\n[!] LOI: Tai khoan nguoi nhan khong ton tai!\n";
//         _getch();
//         return;
//     }

//     // 3. Thông tin giao dịch
//     long long amount;
//     cout << "Nhap so tien: ";
//     cin >> amount;

//     string pin;
//     cout << "Nhap ma PIN: ";
//     cin >> pin;

//     // 4. Thực thi
//     auto trans = make_shared<TransferTransaction>(srcAcc, destAcc, amount, pin);
//     TransferCmd cmd(trans);

//     cout << "\nDang xu ly...\n";
//     cmd.execute();

//     cout << "\n(Ket thuc giao dich)";
//     cout << "\nNhan phim bat ky de quay lai...";
//     _getch();
// }

// void UI::CustomerView::showNotificationsPage()
// {
//     UI::ConsoleUtils::clearScreen();
//     cout << "--- HOP THU DEN (NOTIFICATIONS) ---\n\n";

//     auto bank = AppContext::getInstance().getBankSystem();
//     auto cust = bank->currentCustomer();

//     if (cust)
//     {
//         vector<string> accIds = cust->getOwnedAccountIds();
//         bool hasAnyNotif = false;

//         for (const string &accId : accIds)
//         {
//             auto acc = bank->getAccount(accId);
//             if (acc && !acc->notifications().empty())
//             {
//                 hasAnyNotif = true;
//                 cout << ">> Tai khoan " << accId << ":\n";

//                 // Dùng Command để in thông báo (Tái sử dụng code)
//                 ShowNotificationsCmd cmd(acc);
//                 cmd.execute();

//                 cout << "------------------------------------\n";
//             }
//         }

//         if (!hasAnyNotif)
//         {
//             cout << "Hien tai khong co thong bao nao.\n";
//         }
//     }

//     cout << "\nNhan phim bat ky de quay lai...";
//     _getch();
// }

// void UI::CustomerView::showAccountDetailPage(std::string accountNumber)
// {
//     // Lấy object Account thực
//     auto account = _bankSystem->getAccount(accountNumber);
//     if (!account)
//         return;

//     bool inAccountMenu = true;
//     while (inAccountMenu)
//     {
//         // Cập nhật title với số dư mới nhất
//         string title = "--- TAI KHOAN: " + accountNumber + " ---\n" + account->info();
//         int choice = navigateMenu(_accountMenuOptions, title);

//         switch (choice)
//         {
//         case 1: // Thong tin
//             UI::ConsoleUtils::clearScreen();
//             cout << account->info() << "\nNhan phim bat ky...";
//             _getch();
//             break;
//         case 2: // Thong bao
//             UI::ConsoleUtils::clearScreen();
//             // Hiển thị notification từ Account
//             {
//                 auto notifs = account->notifications();
//                 if (notifs.empty())
//                     cout << "Khong co thong bao.\n";
//                 else
//                     for (auto &n : notifs)
//                         cout << "- " << n << "\n";
//             }
//             cout << "\nNhan phim bat ky...";
//             _getch();
//             break;
//         case 3: // Nap tien
//             showDepositPage(accountNumber);
//             break;
//         case 4: // Rut tien
//             showWithdrawPage(accountNumber);
//             break;
//         case 5: // Chuyen tien
//             UI::ConsoleUtils::clearScreen();
//             cout << "Chuc nang chuyen tien dang phat trien...\nNhan phim bat ky...";
//             _getch();
//             break;
//         case 6: // Xoa tai khoan
//             UI::ConsoleUtils::clearScreen();
//             cout << "----Xoa tai khoan----\n";
//             cout << "Nhap PIN de xac nhan: ";
//             {
//                 string pin;
//                 std::getline(cin, pin);
//                 if (account->verifyPIN(pin))
//                 {
//                     _currentCustomer->removeAccount(accountNumber);
//                     _bankSystem->removeAccount(accountNumber);
//                     cout << "\nDa xoa tai khoan.\nNhan phim bat ky...";
//                     _getch();
//                     inAccountMenu = false;
//                 }
//                 else
//                 {
//                     cout << "\nSai PIN.\nNhan phim bat ky...";
//                     _getch();
//                 }
//             }
//             break;
//         case 7: // Quay lai
//             inAccountMenu = false;
//             break;
//         }
//     }
// }

// void UI::CustomerView::showDepositPage(std::string accountNumber)
// {
//     auto account = _bankSystem->getAccount(accountNumber);
//     if (!account)
//         return;

//     bool staying = true;
//     while (staying)
//     {
//         UI::ConsoleUtils::clearScreen();
//         cout << "---- Nap tien ----\n";
//         cout << "Tai khoan: " << accountNumber << "\n";
//         cout << "So du hien tai: " << account->balance() << "\n";
//         cout << "So tien nap: ";

//         long long amount;
//         cin >> amount;
//         cin.ignore();

//         account->deposit(amount);
//         // Có thể thêm log notification vào account ở đây
//         account->addNotification("Nap tien: +" + std::to_string(amount));

//         cout << "\nNap thanh cong! So du moi: " << account->balance();
//         cout << "\nNhan Q de quay lai, phim bat ky de tiep tuc.";

//         char key = _getch();
//         if (key == 'q' || key == 'Q')
//             staying = false;
//     }
// }

// void UI::CustomerView::showWithdrawPage(std::string accountNumber)
// {
//     auto account = _bankSystem->getAccount(accountNumber);
//     if (!account)
//         return;

//     bool staying = true;
//     while (staying)
//     {
//         UI::ConsoleUtils::clearScreen();
//         cout << "---- Rut tien ----\n";
//         cout << "Tai khoan: " << accountNumber << "\n";
//         cout << "So du hien tai: " << account->balance() << "\n";

//         long long amount;
//         cout << "So tien rut: ";
//         cin >> amount;
//         cin.ignore();

//         string pin;
//         cout << "Ma PIN: ";
//         std::getline(cin, pin);

//         if (account->verifyPIN(pin))
//         {
//             if (account->balance() >= amount)
//             {
//                 account->withdraw(amount);
//                 account->addNotification("Rut tien: -" + std::to_string(amount));
//                 cout << "\nRut tien thanh cong! So du moi: " << account->balance();
//                 cout << "\nNhan Q de quay lai.";
//             }
//             else
//             {
//                 cout << "\nSo du khong du!";
//                 _getch();
//                 continue;
//             }
//         }
//         else
//         {
//             cout << "\nSai ma PIN!";
//             _getch();
//             continue;
//         }

//         char key = _getch();
//         if (key == 'q' || key == 'Q')
//             staying = false;
//     }
// }

void UI::CustomerView::handleLogout()
{
    UI::ConsoleUtils::clearScreen();
    cout << "Dang dang xuat...\n";
    _currentCustomer = nullptr;
    LogoutCmd logOut;
    logOut.execute();
    // Logic thoát sẽ được xử lý bởi biến running = false ở trên
}
