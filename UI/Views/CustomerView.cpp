#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"

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

// 3. Include các Transaction
#include "../../Entity/Transaction/DepositTransaction.h"
#include "../../Entity/Transaction/WithdrawTransaction.h"
#include "../../Entity/Transaction/TransferTransaction.h"

#include <iostream>
#include <conio.h>
#include <iomanip>

using namespace std;

UI::CustomerView::CustomerView()
{
    // Khởi tạo danh sách menu 8 chức năng
    _menuOptions = {
        "1. Thong tin nguoi dung",
        "2. Danh sach tai khoan",
        "3. Them tai khoan moi",     // Chức năng tạo tài khoản
        "4. Nap tien",
        "5. Rut tien",
        "6. Chuyen khoan",
        "7. Xem thong bao",
        "8. Dang xuat"
    };
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
        cout << "Xin chao: " << name << "\n\n";
        cout << "--------------- MENU --------------------\n\n";
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string& option : _menuOptions)
        {
            cout << "   " << option << "\n\n";
        }
        // Vẽ con trỏ mũi tên (->) tại vị trí được chọn
        // Công thức tính tọa độ Y: startY + (index - 1) * 2
        int cursorY = startY + (_selectedIndex - 1) * 2;
        UI::ConsoleUtils::goToXY(1, cursorY);
        cout << "->";
        UI::ConsoleUtils::goToXY(1, cursorY); // Đưa con trỏ về lại đầu dòng

        // Vòng lặp bắt phím điều hướng
        while (true)
        {
            char key = _getch(); // Nhận phím

            // Xóa mũi tên ở vị trí cũ
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
            cout << "  ";

            // Xử lý phím lên (W)
            if (key == 'w' || key == 'W')
            {
                if (_selectedIndex > 1)
                    _selectedIndex--;
                else
                    _selectedIndex = (int)_menuOptions.size(); // Vòng xuống cuối
            }
            // Xử lý phím xuống (S)
            else if (key == 's' || key == 'S')
            {
                if (_selectedIndex < (int)_menuOptions.size())
                    _selectedIndex++;
                else
                    _selectedIndex = 1; // Vòng lên đầu
            }
            // Xử lý phím Enter (Chọn)
            else if (key == 13)
            {
                switch (_selectedIndex)
                {
                case 1: showUserInfoPage(); break;
                case 2: showAccountListPage(); break;
                case 3: showAddAccountPage(); break;
                case 4: handleDeposit(); break;
                case 5: handleWithdraw(); break;
                case 6: handleTransfer(); break;
                case 7: showNotificationsPage(); break;
                case 8: handleLogout(); running = false; break;
                }
                break; // Thoát vòng lặp phím để vẽ lại màn hình menu chính
            }

            // Vẽ lại mũi tên ở vị trí mới
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
            cout << "->";
            UI::ConsoleUtils::goToXY(1, startY + (_selectedIndex - 1) * 2);
        }
    }
}

// =========================================================
// HÀM HỖ TRỢ (HELPER)
// =========================================================

// Hàm này giúp nhập và kiểm tra xem tài khoản có thuộc về khách hàng không
// Tránh việc lặp lại code kiểm tra ở các hàm Nạp/Rút/Chuyển
shared_ptr<Account> UI::CustomerView::inputOwnedAccount(string prompt)
{
    string accNum;
    cout << prompt;
    cin >> accNum;

    auto cust = AppContext::getInstance().getBankSystem()->currentCustomer();
    
    // Hàm getAccount của Customer đã kiểm tra quyền sở hữu
    auto acc = cust->getAccount(accNum);

    if (!acc)
    {
        cout << "\n[!] LOI: Tai khoan khong ton tai hoac khong thuoc ve ban!\n";
        return nullptr;
    }
    return acc;
}

// =========================================================
// CÁC TRANG CHỨC NĂNG CƠ BẢN
// =========================================================

void UI::CustomerView::showUserInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    auto cust = AppContext::getInstance().getBankSystem()->currentCustomer();
    
    cout << "--- THONG TIN CA NHAN ---\n\n";
    if (cust)
    {
        cout << cust->info() << endl;
    }
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAccountListPage()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- DANH SACH TAI KHOAN ---\n\n";

    auto bank = AppContext::getInstance().getBankSystem();
    auto cust = bank->currentCustomer();

    if (cust)
    {
        // Cần hàm getOwnedAccountIds() public trong Customer
        vector<string> accIds = cust->getOwnedAccountIds();
        
        if (accIds.empty()) {
            cout << "Ban chua co tai khoan nao.\n";
        } else {
            for (const string& accId : accIds)
            {
                auto acc = bank->getAccount(accId);
                if (acc)
                {
                    cout << "+ " << acc->info() << endl;
                }
            }
        }
    }
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAddAccountPage()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- MO TAI KHOAN MOI ---\n\n";

    auto bank = AppContext::getInstance().getBankSystem();
    auto cust = bank->currentCustomer();

    if (!cust) return;

    string newAccNum, pin;
    long long initBal;

    cout << "Nhap so tai khoan muon tao (VD: 123456): ";
    cin >> newAccNum;

    // Kiểm tra trùng lặp trong toàn hệ thống ngân hàng
    if (bank->getAccount(newAccNum) != nullptr)
    {
        cout << "\n[!] LOI: So tai khoan nay da ton tai. Vui long chon so khac.\n";
        cout << "Nhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    cout << "Nhap ma PIN (mat khau giao dich): ";
    cin >> pin;
    cout << "Nhap so du ban dau (VND): ";
    cin >> initBal;

    // Tạo tài khoản CheckingAccount
    auto newAcc = make_shared<CheckingAccount>(newAccNum, cust->getName(), initBal, pin);

    // Thêm vào Customer (Hàm này sẽ tự gọi bank->addAccount)
    cust->addAccount(newAcc);

    cout << "\n[OK] Mo tai khoan thanh cong!\n";
    cout << "So tai khoan: " << newAccNum << endl;
    cout << "So du: " << initBal << " VND\n";
    
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

// =========================================================
// CÁC CHỨC NĂNG GIAO DỊCH (TRANSACTIONS)
// =========================================================

void UI::CustomerView::handleDeposit()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- NAP TIEN ---\n\n";

    // 1. Nhập tài khoản nguồn (của mình)
    auto acc = inputOwnedAccount("Nhap so tai khoan nhan tien: ");
    if (!acc) { _getch(); return; }

    // 2. Nhập số tiền
    long long amount;
    cout << "Nhap so tien muon nap: ";
    cin >> amount;

    // 3. Tạo Transaction & Command
    auto trans = make_shared<DepositTransaction>(acc, amount);
    DepositCmd cmd(trans);

    // 4. Thực thi
    cmd.execute();
    
    // In kết quả (Transaction tự cập nhật số dư, ta chỉ cần in ra)
    cout << "\n[OK] Giao dich hoan tat.\n";
    cout << "So du moi: " << acc->balance() << " VND\n";
    
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::handleWithdraw()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- RUT TIEN ---\n\n";

    auto acc = inputOwnedAccount("Nhap so tai khoan rut tien: ");
    if (!acc) { _getch(); return; }

    long long amount;
    cout << "Nhap so tien muon rut: ";
    cin >> amount;

    string pin;
    cout << "Nhap ma PIN: ";
    cin >> pin;

    // Tạo Transaction Rút tiền
    auto trans = make_shared<WithdrawTransaction>(acc, amount, pin);
    WithdrawCmd cmd(trans);
    
    // Thực thi (Logic kiểm tra PIN và Số dư nằm trong Transaction::execute)
    cout << "\nDang xu ly...\n";
    cmd.execute();

    cout << "\n(Ket thuc giao dich)";
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::handleTransfer()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- CHUYEN KHOAN ---\n\n";

    // 1. Tài khoản nguồn (Của mình)
    auto srcAcc = inputOwnedAccount("TK Nguon (Cua ban): ");
    if (!srcAcc) { _getch(); return; }

    // 2. Tài khoản đích (Của bất kỳ ai trong hệ thống)
    string destId;
    cout << "TK Nhan (Nguoi khac): ";
    cin >> destId;

    auto bank = AppContext::getInstance().getBankSystem();
    auto destAcc = bank->getAccount(destId);

    if (!destAcc)
    {
        cout << "\n[!] LOI: Tai khoan nguoi nhan khong ton tai!\n";
        _getch(); return;
    }

    // 3. Thông tin giao dịch
    long long amount;
    cout << "Nhap so tien: "; cin >> amount;
    
    string pin;
    cout << "Nhap ma PIN: "; cin >> pin;

    // 4. Thực thi
    auto trans = make_shared<TransferTransaction>(srcAcc, destAcc, amount, pin);
    TransferCmd cmd(trans);
    
    cout << "\nDang xu ly...\n";
    cmd.execute();

    cout << "\n(Ket thuc giao dich)";
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

// =========================================================
// CHỨC NĂNG THÔNG BÁO & LOGOUT
// =========================================================

void UI::CustomerView::showNotificationsPage()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- HOP THU DEN (NOTIFICATIONS) ---\n\n";

    auto bank = AppContext::getInstance().getBankSystem();
    auto cust = bank->currentCustomer();

    if (cust)
    {
        vector<string> accIds = cust->getOwnedAccountIds();
        bool hasAnyNotif = false;

        for (const string& accId : accIds)
        {
            auto acc = bank->getAccount(accId);
            if (acc && !acc->notifications().empty())
            {
                hasAnyNotif = true;
                cout << ">> Tai khoan " << accId << ":\n";
                
                // Dùng Command để in thông báo (Tái sử dụng code)
                ShowNotificationsCmd cmd(acc);
                cmd.execute();
                
                cout << "------------------------------------\n";
            }
        }

        if (!hasAnyNotif)
        {
            cout << "Hien tai khong co thong bao nao.\n";
        }
    }
    
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::handleLogout()
{
    UI::ConsoleUtils::clearScreen();
    std::cout << "Dang dang xuat...\n";
    // Logic thoát sẽ được xử lý bởi biến running = false ở trên
}
