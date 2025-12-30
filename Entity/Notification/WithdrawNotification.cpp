#include "WithdrawNotification.h"
#include <sstream>

WithdrawNotification::WithdrawNotification(std::shared_ptr<Transaction> transaction) 
    : Notification(transaction) {
    // do nothing
}

std::string WithdrawNotification::makeMessage() {
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Rut tien thanh cong " << amount << " VND.";
    return ss.str();
}

std::string WithdrawNotification::message() {
    return makeMessage();
}

std::string WithdrawNotification::info() {
    std::stringstream ss;
    ss << "[RUT TIEN] " << _time << " | " << makeMessage();
    return ss.str();
}