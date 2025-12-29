#include "DepositTransaction.h"
#include "../Notification/DepositNotification.h"
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

void DepositTransaction::execute()
{
    _srcAccount->deposit(_amount);
}
