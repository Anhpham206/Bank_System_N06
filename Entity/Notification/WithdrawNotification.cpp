#include "WithdrawNotification.h"
#include <sstream>

WithdrawNotification::WithdrawNotification(std::shared_ptr<Transaction> transaction)
    : Notification(transaction)
{
    // do nothing
}

std::string WithdrawNotification::makeMessage()
{
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Rut tien thanh cong " << amount << " VND.";
    return ss.str();
}

std::string WithdrawNotification::message()
{
    return _time + ": " + makeMessage();
}

std::string WithdrawNotification::info()
{
    std::stringstream ss;
    ss << "--------- THONG BAO ---------\n";
    ss << "Thoi gian: " << _time << "\n";
    ss << "Noi dung : " << makeMessage() << "\n";
    ss << "-----------------------------\n";
    return ss.str();
}