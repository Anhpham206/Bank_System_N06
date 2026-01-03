#include "DepositNotification.h"
#include <sstream>

DepositNotification::DepositNotification(std::shared_ptr<Transaction> transaction)
    : Notification(transaction)
{
    // do nothing
}

std::string DepositNotification::makeMessage()
{
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Tai khoan da duoc nap " << amount << " VND.";
    return ss.str();
}

std::string DepositNotification::message()
{
    return _time + ": " + makeMessage();
}

std::string DepositNotification::info()
{
    std::stringstream ss;
    ss << "--------- THONG BAO ---------\n";
    ss << "Thoi gian: " << _time << "\n";
    ss << "Noi dung : " << makeMessage() << "\n";
    ss << "-----------------------------\n";
    return ss.str();
}