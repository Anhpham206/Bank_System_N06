#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"

<<<<<<< HEAD
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
=======
#include "../../Entity/Account/SavingAccount.h"
#include "../../Entity/Account/CheckingAccount.h"
#include "../../Entity/BankSystem/BankSystem.h"
#include "../../Entity/Customer/Customer.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <vector>

using std::cout, std::cin;
using std::string;
using std::vector;
using std::shared_ptr;
using std::make_shared;
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43

UI::CustomerView::CustomerView(shared_ptr<BankSystem> system, shared_ptr<Customer> customer)
{
<<<<<<< HEAD
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
=======
    _bankSystem = system;
    _currentCustomer = customer;

    _menuOptions = {
        "Thong tin nguoi dung",
        "Danh sach tai khoan",
        "Them tai khoan",
        "Dang xuat"};

    _accountMenuOptions = {
        "Thong tin tai khoan",
        "Thong bao",
        "Nap tien",
        "Rut tien",
        "Chuyen tien",
        "Xoa tai khoan",
        "Quay lai"};

    _selectedIndex = 1;
}

int UI::CustomerView::navigateMenu(const std::vector<std::string>& options, std::string title) {
    bool selecting = true;
    int index = 1;
    
    while (selecting) {
        UI::ConsoleUtils::clearScreen();
        cout << title << "\n\n";
        
        int startY = UI::ConsoleUtils::getWhereY();
        for (const string& op : options) {
            cout << "   " << op << "\n\n";
        }

        int cursorY = startY + (index - 1) * 2; 
        UI::ConsoleUtils::goToXY(1, cursorY);
        cout << "->"; 
        UI::ConsoleUtils::goToXY(1, cursorY);

        char key = _getch();
        if (key == 'w' || key == 'W') {
            if (index > 1) index--;
        }
        else if (key == 's' || key == 'S') {
            if (index < (int)options.size()) index++;
        }
        else if (key == 13) { // Enter
            return index;
        }
    }
    return 0;
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
}

void UI::CustomerView::render()
{
    bool running = true;
    while (running)
    {
<<<<<<< HEAD
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
=======
        string title = "------NGAN HANG N06------\nChao mung khach hang: Anh \n------MENU------";
        // [THAY ĐỔI] Sử dụng hàm navigateMenu thay vì viết lại logic switch-case dài dòng
        int choice = navigateMenu(_menuOptions, title);

        switch (choice)
        {
        case 1: showUserInfoPage(); break;
        case 2: showAccountListPage(); break;
        case 3: showAddAccountPage(); break;
        case 4: 
            handleLogout(); 
            running = false; 
            break;
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
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
<<<<<<< HEAD
    auto cust = AppContext::getInstance().getBankSystem()->currentCustomer();
    
    cout << "--- THONG TIN CA NHAN ---\n\n";
    if (cust)
    {
        cout << cust->info() << endl;
=======
    cout << "--- TRANG THONG TIN NGUOI DUNG ---\n";
    if (_currentCustomer) {
        cout << _currentCustomer->info() << "\n";
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
    }
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAccountListPage()
{
<<<<<<< HEAD
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
=======
    // Lấy danh sách ID tài khoản từ Customer
    vector<string> myAccountIds = _currentCustomer->getOwnedAccountIds();
    vector<string> displayOptions;

    // Duyệt qua từng ID để lấy thông tin chi tiết từ BankSystem (hoặc Customer->getAccount)
    for (const string& accId : myAccountIds) {
        auto acc = _bankSystem->getAccount(accId);
        if (acc) {
            displayOptions.push_back(acc->info()); 
        } else {
            displayOptions.push_back("Error loading: " + accId);
        }
    }
    displayOptions.push_back("Quay lai");

    string title = "--- DANH SACH TAI KHOAN ---\nChon tai khoan de giao dich:";
    int choice = navigateMenu(displayOptions, title);

    // Nếu chọn một tài khoản (không phải nút Quay lai)
    if (choice > 0 && choice < (int)displayOptions.size()) {
        string selectedStr = displayOptions[choice - 1];
        // Cắt chuỗi để lấy Account Number (Giả sử định dạng info là "Account No: 123456 | ...")
        // Tìm vị trí chuỗi "Account No: " và lấy số phía sau
        size_t startPos = selectedStr.find("Account No: ");
        if (startPos != string::npos) {
            startPos += 12; // Độ dài của "Account No: "
            size_t endPos = selectedStr.find(" |", startPos);
            string accNum = selectedStr.substr(startPos, endPos - startPos);
            showAccountDetailPage(accNum);
        } else {
            // Fallback nếu format khác: Lấy từ list ID gốc
            showAccountDetailPage(myAccountIds[choice - 1]);
        }
    }
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
}

void UI::CustomerView::showAddAccountPage()
{
    UI::ConsoleUtils::clearScreen();
<<<<<<< HEAD
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
=======
    cout << "--- THEM TAI KHOAN MOI ---\n";
    cout << "Loai tai khoan:\n";
    cout << "1. Saving Account (Tiet kiem)\n";
    cout << "2. Checking Account (Vang lai)\n";
    cout << "Chon (1/2): ";
    char type; cin >> type; cin.ignore();

    string accNum, pin, confirmPin;
    cout << "\n--- Tao tai khoan ---\n";
    cout << "Account number: "; std::getline(cin, accNum);
    
    // Kiểm tra trùng
    if (_bankSystem->getAccount(accNum) != nullptr) {
        cout << "\nLoi: So tai khoan da ton tai!\nNhan phim bat ky...";
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
        _getch();
        return;
    }

<<<<<<< HEAD
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
=======
    cout << "Ma PIN: "; std::getline(cin, pin);
    cout << "Xac nhan ma PIN: "; std::getline(cin, confirmPin);

    if (pin != confirmPin) {
        cout << "\nMa PIN khong khop!\nNhan phim bat ky...";
        _getch();
        return;
    }

    // Tạo Account dựa trên Type
    shared_ptr<Account> newAccount = nullptr;
    string ownerName = _currentCustomer->getName();

    if (type == '1') {
        // SavingAccount constructor: accNum, owner, balance, pin, rate
        newAccount = make_shared<SavingAccount>(accNum, ownerName, 0, pin, 0.05); // Lãi suất mặc định 5%
    } else {
        // CheckingAccount constructor: accNum, owner, balance, pin
        newAccount = make_shared<CheckingAccount>(accNum, ownerName, 0, pin);
    }

    if (newAccount) {
        _currentCustomer->addAccount(newAccount); 
        
        cout << "\nTao tai khoan thanh cong!\nNhan phim bat ky de quay lai...";
    }
>>>>>>> 786cb0ccf22f8015505b8e1dbc9fbad0a1639d43
    _getch();
}

void UI::CustomerView::showAccountDetailPage(std::string accountNumber)
{
    // Lấy object Account thực
    auto account = _bankSystem->getAccount(accountNumber);
    if (!account) return;

    bool inAccountMenu = true;
    while(inAccountMenu) {
        // Cập nhật title với số dư mới nhất
        string title = "--- TAI KHOAN: " + accountNumber + " ---\n" + account->info();
        int choice = navigateMenu(_accountMenuOptions, title);

        switch (choice) {
            case 1: // Thong tin
                UI::ConsoleUtils::clearScreen();
                cout << account->info() << "\nNhan phim bat ky...";
                _getch();
                break;
            case 2: // Thong bao
                UI::ConsoleUtils::clearScreen();
                // Hiển thị notification từ Account
                {
                    auto notifs = account->notifications();
                    if (notifs.empty()) cout << "Khong co thong bao.\n";
                    else for (auto& n : notifs) cout << "- " << n << "\n";
                }
                cout << "\nNhan phim bat ky...";
                _getch();
                break;
            case 3: // Nap tien
                showDepositPage(accountNumber);
                break;
            case 4: // Rut tien
                showWithdrawPage(accountNumber);
                break;
            case 5: // Chuyen tien
                UI::ConsoleUtils::clearScreen();
                cout << "Chuc nang chuyen tien dang phat trien...\nNhan phim bat ky...";
                _getch();
                break;
            case 6: // Xoa tai khoan
                UI::ConsoleUtils::clearScreen();
                cout << "----Xoa tai khoan----\n";
                cout << "Nhap PIN de xac nhan: ";
                {
                    string pin; std::getline(cin, pin);
                    if (account->verifyPIN(pin)) {
                        _currentCustomer->removeAccount(accountNumber);
                        _bankSystem->removeAccount(accountNumber);
                        cout << "\nDa xoa tai khoan.\nNhan phim bat ky...";
                        _getch();
                        inAccountMenu = false;
                    } else {
                        cout << "\nSai PIN.\nNhan phim bat ky...";
                        _getch();
                    }
                }
                break;
            case 7: // Quay lai
                inAccountMenu = false;
                break;
        }
    }
}

void UI::CustomerView::showDepositPage(std::string accountNumber)
{
    auto account = _bankSystem->getAccount(accountNumber);
    if (!account) return;

    bool staying = true;
    while(staying) {
        UI::ConsoleUtils::clearScreen();
        cout << "---- Nap tien ----\n";
        cout << "Tai khoan: " << accountNumber << "\n";
        cout << "So du hien tai: " << account->balance() << "\n";
        cout << "So tien nap: ";
        
        long long amount; cin >> amount; cin.ignore();
        
        account->deposit(amount);
        // Có thể thêm log notification vào account ở đây
        account->addNotification("Nap tien: +" + std::to_string(amount));
        
        cout << "\nNap thanh cong! So du moi: " << account->balance();
        cout << "\nNhan Q de quay lai, phim bat ky de tiep tuc.";
        
        char key = _getch();
        if (key == 'q' || key == 'Q') staying = false;
    }
}

void UI::CustomerView::showWithdrawPage(std::string accountNumber)
{
    auto account = _bankSystem->getAccount(accountNumber);
    if (!account) return;

    bool staying = true;
    while(staying) {
        UI::ConsoleUtils::clearScreen();
        cout << "---- Rut tien ----\n";
        cout << "Tai khoan: " << accountNumber << "\n";
        cout << "So du hien tai: " << account->balance() << "\n";
        
        long long amount;
        cout << "So tien rut: "; cin >> amount; cin.ignore();
        
        string pin;
        cout << "Ma PIN: "; std::getline(cin, pin);

        if (account->verifyPIN(pin)) {
            if (account->balance() >= amount) {
                account->withdraw(amount);
                account->addNotification("Rut tien: -" + std::to_string(amount));
                cout << "\nRut tien thanh cong! So du moi: " << account->balance();
                cout << "\nNhan Q de quay lai.";
            } else {
                cout << "\nSo du khong du!";
                _getch();
                continue;
            }
        } else {
            cout << "\nSai ma PIN!";
            _getch();
            continue;
        }

        char key = _getch();
        if (key == 'q' || key == 'Q') staying = false;
    }
}

void UI::CustomerView::handleLogout()
{
    UI::ConsoleUtils::clearScreen();
    cout << "Dang dang xuat...\n";
    _currentCustomer = nullptr;
    // Logic thoát sẽ được xử lý bởi biến running = false ở trên
}
