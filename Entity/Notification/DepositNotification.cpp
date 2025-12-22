#include "DepositNotification.h"
#include <sstream>

DepositNotification::DepositNotification(std::shared_ptr<Transaction> transaction) //
    : Notification(transaction) {
        // Do nothing
}

std::string DepositNotification::makeMessage() {
    // Truy cập dữ liệu qua _transaction (là shared_ptr, truy cập bằng ->)
    long long amount = _transaction ? _transaction->amount() : 0; //
    
    std::stringstream ss;
    ss << "Tai khoan cua quy khach da nhan duoc so tien " << amount << " VND vao luc " << _time << ".";
    return ss.str();
}

std::string DepositNotification::message() {
    return makeMessage();
}

std::string DepositNotification::info() {
    return "Deposit Notification [" + _time + "]";
}