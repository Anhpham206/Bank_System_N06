#include "TransferNotification.h"
#include <sstream>

TransferNotification::TransferNotification(std::shared_ptr<Transaction> transaction) 
    : Notification(transaction) {
        // Do nothing
}

std::string TransferNotification::makeMessage() {
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "A transfer of " << amount << " VND was processed.";
    return ss.str();
}

std::string TransferNotification::message() {
    return makeMessage();
}

std::string TransferNotification::info() {
    std::stringstream ss;
    ss << "Transfer Notification | Time: " << _time 
       << " | Msg: " << makeMessage();
    return ss.str();
}