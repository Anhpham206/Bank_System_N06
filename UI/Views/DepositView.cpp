#include "DepositView.h"
#include "../Utils/ConsoleUtils.h"
#include "../../Helper/Utils.h"
#include "../../Entity/Command/DepositCmd.h"
#include "../../Business/ParserFactory/ParserFactory.h"
#include "../../Business/IParsable.h"
#include "../../Business/AppContext.h"
#include "../../Entity/Account/Account.h"
#include "../../Entity/Transaction/DepositTransaction.h"

#include <iostream>
#include <conio.h>

using std::cout;

UI::DepositView::DepositView(shared_ptr<Account> account)
    : _account(account)
{
}

void UI::DepositView::render()
{
    UI::ConsoleUtils::clearScreen();
    cout << "=========================================\n";
    cout << "              NGAN HANG N06              \n";
    cout << "=========================================\n\n";
    cout << "--------------- NAP TIEN ----------------\n\n";

    // Nhập số tiền
    cout << "Nhap so tien can nap: ";
    string amountStr = Utils::inputNumber(15);
    cout << "\n";

    // Tạo transaction bằng parser
    ParserFactory factory;
    IParsable *parser = factory.create("DepositTransaction");
    auto obj = parser->parse(_account->accountNumber() + ", " + amountStr);
    std::shared_ptr<DepositTransaction> trans = std::dynamic_pointer_cast<DepositTransaction>(obj);

    DepositCmd cmd(trans);

    cout << "Dang xu ly giao dich...\n\n";
    cmd.execute();

    cout << "\nNhan phim bat ky de quay lai...";
    _getch();
}
