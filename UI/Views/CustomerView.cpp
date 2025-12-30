#include "CustomerView.h"
#include "../Utils/ConsoleUtils.h"

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

UI::CustomerView::CustomerView(shared_ptr<BankSystem> system, shared_ptr<Customer> customer)
{
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
}

void UI::CustomerView::render()
{
    bool running = true;
    while (running)
    {
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
        }
    }
}

// --- Các hàm giả lập chuyển trang ---
void UI::CustomerView::showUserInfoPage()
{
    UI::ConsoleUtils::clearScreen();
    cout << "--- TRANG THONG TIN NGUOI DUNG ---\n";
    if (_currentCustomer) {
        cout << _currentCustomer->info() << "\n";
    }
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}

void UI::CustomerView::showAccountListPage()
{
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
}

void UI::CustomerView::showAddAccountPage()
{
    UI::ConsoleUtils::clearScreen();
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
        _getch();
        return;
    }

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
