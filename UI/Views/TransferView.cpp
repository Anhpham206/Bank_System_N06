#include "TransferView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Helper/Utils.h"
#include "../../Entity/Command/TransferCmd.h"
#include "../../Entity/Transaction/TransferTransaction.h"

#include <iostream>
#include <conio.h>

using std::cout;

// Constructor nhận vào User và BankSystem
UI::TransferView::TransferView(shared_ptr<BankSystem> bank, shared_ptr<Customer> user) 
    : _bank(bank), _user(user) {}

void UI::TransferView::render() {
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "             CHUYEN KHOAN                \n";
    cout << "=========================================\n\n";

    // 1. Nhập TK Nguồn (Của mình)
    cout << "Nhap TK Nguon (Cua ban, 10 so): ";
    string srcId = Utils::inputNumber(10);
    cout << "\n";
    
    auto srcAcc = _user->getAccount(srcId);
    if (!srcAcc) {
        cout << "[!] Ban khong so huu tai khoan nay!\nNhan phim bat ky...";
        _getch(); return;
    }

    // 2. Nhập TK Đích
    cout << "Nhap TK Nguoi nhan (10 so): ";
    string destId = Utils::inputNumber(10);
    cout << "\n";

    auto destAcc = _bank->getAccount(destId);
    if (!destAcc) {
        cout << "[!] Tai khoan nguoi nhan khong ton tai!\nNhan phim bat ky...";
        _getch(); return;
    }

    // 3. Nhập số tiền 
    cout << "Nhap so tien chuyen: ";
    string amountStr = Utils::inputNumber(15); 
    long long amount = stoll(amountStr);
    cout << "\n";

    // 4. Nhập PIN
    cout << "Nhap ma PIN (6 so): ";
    string pin = Utils::inputNumber(6);
    cout << "\n";

    // 5. Kiểm tra logic sơ bộ trước khi tạo Command (hoặc để Transaction lo)
    if (!srcAcc->verifyPIN(pin)) {
        cout << "[!] Sai ma PIN!\nNhan phim bat ky...";
        _getch(); return;
    }
    if (srcAcc->balance() < amount) {
        cout << "[!] So du khong du!\nNhan phim bat ky...";
        _getch(); return;
    }

    // 6. Thực thi Command
    // Lưu ý: TransferTransaction cần constructor hỗ trợ PIN, hoặc set PIN sau
    // Giả sử constructor: (id, src, dest, amount) - PIN check ở trên rồi
    auto trans = make_shared<TransferTransaction>("TRA_AUTO", srcAcc, destAcc, amount); 
    TransferCmd cmd(trans);
    
    cout << "Dang xu ly giao dich...\n";
    cmd.execute();

    cout << "\n[THANH CONG] Giao dich hoan tat.\n";
    cout << "So du moi: " << srcAcc->balance() << "\n";
    cout << "Nhan phim bat ky de quay lai...";
    _getch();
}