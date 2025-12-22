#include "WithdrawNotification.h"
#include <sstream>

// Cập nhật constructor để nhận shared_ptr
WithdrawNotification::WithdrawNotification(std::shared_ptr<Transaction> transaction) 
    : Notification(transaction) {
        // Do nothing
}

std::string WithdrawNotification::makeMessage() {
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "A withdrawal of " << amount << " VND was successful.";
    return ss.str();
}

std::string WithdrawNotification::message() {
    return makeMessage();
}

std::string WithdrawNotification::info() {
    std::stringstream ss;
    ss << "Withdrawal Notification | Time: " << _time 
       << " | Msg: " << makeMessage();
    return ss.str();
}