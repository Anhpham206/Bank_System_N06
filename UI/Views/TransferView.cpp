#include "TransferView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Helper/Utils.h"
#include "../../Entity/Command/TransferCmd.h"
#include "../../Entity/Transaction/TransferTransaction.h"
#include "../../Business/AppContext.h"
#include "../../Entity/Account/Account.h"
#include "../../Business/ParserFactory/ParserFactory.h"
#include "../../Business/IParsable.h"

#include <iostream>
#include <conio.h>

using std::cout;

// Constructor nhận vào User và BankSystem
UI::TransferView::TransferView(shared_ptr<Account> account)
    : _account(account)
{
    _bank = AppContext::getInstance().getBankSystem();
}

void UI::TransferView::render()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n\n";

    cout << "------------- CHUYEN KHOAN --------------\n\n";

    // 2. Nhập TK Đích
    cout << "Nhap TK Nguoi nhan (10 so): ";
    string destId = Utils::inputNumberFixedLength(10);
    cout << "\n";

    auto destAcc = _bank->getAccount(destId);
    if (!destAcc)
    {
        cout << "[!] Tai khoan nguoi nhan khong ton tai!\nNhan phim bat ky de quay lai...";
        _getch();
        return;
    }

    // 3. Nhập số tiền
    cout << "Nhap so tien chuyen: ";
    string amountStr = Utils::inputNumber(15);
    cout << "\n";

    // 4. Nhập PIN
    int startY = UI::ConsoleUtils::getWhereY();
    int count = 1;
    string pin;
    while (true)
    {
        cout << "Nhap ma PIN: ";
        pin = Utils::inputNumberFixedLength(6);
        cout << "\n";

        if (_account->verifyPIN(pin))
        {
            break;
        }
        else
        {
            count++;
            if (count > 3)
            {
                cout << "[!] Nhap sai qua 3 lan. Giao dich bi huy.\n\n";
                cout << "Nhan phim bat ky de quay lai...";
                _getch();
                return;
            }
            cout << "[!] Sai ma PIN! Vui long thu lai.\n";
            UI::ConsoleUtils::goToXY(0, startY);
            cout << "                      ";
            UI::ConsoleUtils::goToXY(0, startY);
        }
    }

    ParserFactory factory;
    IParsable *parser = factory.create("TransferTransaction");
    auto trans = std::static_pointer_cast<TransferTransaction>(std::shared_ptr<Object>(
        parser->parse(_account->accountNumber() + ", " + destAcc->accountNumber() + ", " + amountStr)));
    TransferCmd cmd(trans);

    cout << "Dang xu ly giao dich...               \n\n";
    cmd.execute();
    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}