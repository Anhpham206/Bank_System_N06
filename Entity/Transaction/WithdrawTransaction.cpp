#include "WithdrawTransaction.h"
#include "../Notification/WithdrawNotification.h"
#include "../Command/DisplayInfoCmd.h"
#include "../Account/Account.h"

#include <iostream>
#include <sstream>
#include <format>

WithdrawTransaction::WithdrawTransaction(std::shared_ptr<Account> acc, long long amount)
    : Transaction(acc, amount)
{
}

std::string WithdrawTransaction::info()
{
    std::stringstream ss;
    ss << std::format("Loai giao dich: Rut tien\nLuong tien gia dich:{0}", _amount);
    return ss.str();
}

bool WithdrawTransaction::execute()
{

    if (_srcAccount->balance() >= _amount)
    {
        _srcAccount->withdraw(_amount);
        std::shared_ptr<WithdrawNotification> notification = std::make_shared<WithdrawNotification>(shared_from_this());
        _srcAccount->addNotification(notification->message());
        DisplayInfoCmd displayCmd(notification);
        displayCmd.execute();
        return true;
    }
    else
    {
        std::cout << "Tai khoan hien khong du de thuc hien giao dich!";
        return false;
    }
}

std::shared_ptr<Account> WithdrawTransaction::destAccount()
{
    return nullptr;
}
