#include "DepositTransaction.h"
#include "../Notification/DepositNotification.h"
#include "../Command/DisplayInfoCmd.h"
#include "../Notification/DepositNotification.h"
#include "../Account/Account.h"
#include <iostream>
#include <sstream>

DepositTransaction::DepositTransaction(std::shared_ptr<Account> acc, long long amount)
    : Transaction(acc, amount) {}

std::string DepositTransaction::info()
{
    std::stringstream ss;
    ss << "Loai giao dich: Gui tien\nLuong tien giao dich: " << _amount;
    return ss.str();
}

bool DepositTransaction::execute()
{
    _srcAccount->deposit(_amount);
    std::shared_ptr<DepositNotification> notification = std::make_shared<DepositNotification>(shared_from_this());
    _srcAccount->addNotification(notification->message());
    DisplayInfoCmd displayCmd(notification);
    displayCmd.execute();
    return true;
}

std::shared_ptr<Account> DepositTransaction::destAccount()
{
    return nullptr;
}
