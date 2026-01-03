#include "WithdrawView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Helper/Utils.h"
#include "../../Entity/Command/WithdrawCmd.h"
#include "../../Business/ParserFactory/ParserFactory.h"
#include "../../Business/IParsable.h"
#include "../../Entity/Account/Account.h"
#include "../../Entity/Transaction/WithdrawTransaction.h"

#include <iostream>
#include <conio.h>

using std::cout;

UI::WithdrawView::WithdrawView(shared_ptr<Account> account)
    : _account(account)
{
}

void UI::WithdrawView::render()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n\n";
    cout << "--------------- RUT TIEN ----------------\n\n";

    // Nhập số tiền
    cout << "Nhap so tien can rut: ";
    string amountStr = Utils::inputNumber(15);
    cout << "\n";

    // Nhập PIN và kiểm tra (tối đa 3 lần)
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

    // Tạo transaction bằng parser
    ParserFactory factory;
    IParsable *parser = factory.create("WithdrawTransaction");
    auto obj = parser->parse(_account->accountNumber() + ", " + amountStr);
    std::shared_ptr<WithdrawTransaction> trans = std::dynamic_pointer_cast<WithdrawTransaction>(obj);

    WithdrawCmd cmd(trans);

    cout << "Dang xu ly giao dich...               \n\n";
    cmd.execute();

    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}
