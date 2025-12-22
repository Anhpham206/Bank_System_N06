#include "DepositNotification.h"
#include <sstream>

DepositNotification::DepositNotification(std::shared_ptr<Transaction> transaction) //
    : Notification(transaction) {
        // Do nothing
}

std::string DepositNotification::makeMessage() {
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Your account has been credited with " << amount << " VND.";
    return ss.str();
}

std::string DepositNotification::message() {
    return makeMessage();
}

std::string DepositNotification::info() {
    std::stringstream ss;
    ss << "Deposit Notification | Time: " << _time 
       << " | Msg: " << makeMessage();
    return ss.str();
}