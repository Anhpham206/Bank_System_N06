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
    ss << "Giao dich rut tien " << amount << " VND da duoc thuc hien thanh cong vao luc " << _time << ".";
    return ss.str();
}

std::string WithdrawNotification::message() {
    return makeMessage();
}

std::string WithdrawNotification::info() {
    return "Withdrawal Notification | Time: " + _time + " | Message: " + makeMessage();
}