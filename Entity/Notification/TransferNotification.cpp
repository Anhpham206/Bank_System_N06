#include "TransferNotification.h"
#include <sstream>

TransferNotification::TransferNotification(std::shared_ptr<Transaction> transaction) 
    : Notification(transaction) {
        // Do nothing
}

std::string TransferNotification::makeMessage() {
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Chuyen tien thanh cong " << amount << " VND.";
    return ss.str();
}

std::string TransferNotification::message() {
    return makeMessage();
}

std::string TransferNotification::info() {
    std::stringstream ss;
    ss << "[CHUYEN TIEN] " << _time << " | " << makeMessage();
    return ss.str();
}