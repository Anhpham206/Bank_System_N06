#include "TransferNotification.h"
#include <sstream>

TransferNotification::TransferNotification(std::shared_ptr<Transaction> transaction) 
    : Notification(transaction) {
        // Do nothing
}

std::string TransferNotification::makeMessage() {
    // Truy cập dữ liệu qua _transaction (là shared_ptr)
    long long amount = _transaction ? _transaction->amount() : 0;
    
    std::stringstream ss;
    ss << "Giao dich chuyen tien tri gia " << amount << " VND da duoc thuc hien vao luc " << _time << ".";
    return ss.str();
}

std::string TransferNotification::message() {
    return makeMessage();
}

std::string TransferNotification::info() {
    return "Transfer Notification | Time: " + _time + " | Message: " + makeMessage();
}