#include "TransferTransaction.h"
#include "../Notification/TransferNotification.h"
#include "../Notification/Notification.h"
#include <iostream>
#include <sstream> 

TransferTransaction::TransferTransaction(const std::string& id, std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount)
    : Transaction(id, amount), _sourceAccount(sourceAcc), _destinationAccount(destAcc) {}

std::string TransferTransaction::info() {
    auto src = _sourceAccount.lock();
    auto dest = _destinationAccount.lock();
    
    std::stringstream ss;
    ss << "Transfer    | ID: " << _transactionID 
       << " | Date: " << _date 
       << " | Amount: " << _amount << " VND";

    if (src && dest) {
        ss << " | From: " << src->AccountNumber() 
           << " | To: " << dest->AccountNumber();
    } else {
        ss << " | Error: One or both accounts are unavailable.";
    }
    
    return ss.str();
}

void TransferTransaction::execute() {
    auto src = _sourceAccount.lock();
    auto dest = _destinationAccount.lock();

    if (src && dest) {
        if (src->Balance() >= _amount) {
            src->withdraw(_amount); // Trừ tiền nguồn
            dest->deposit(_amount);  // Cộng tiền đích
            std::cout << "Transaction " << _transactionID << ": Transferred " << _amount << " VND successfully." << std::endl;

            auto transPtr = std::static_pointer_cast<Transaction>(shared_from_this());
            auto notif = std::make_shared<TransferNotification>(transPtr);
            
            src->addNotification(notif); // Thông báo cho người gửi
            dest->addNotification(notif); // Thông báo cho người nhận
        } else {
            std::cout << "Transaction " << _transactionID << ": Transfer failed (Insufficient balance)." << std::endl;
        }
    } else {
        std::cerr << "Execution failed: One or both accounts are missing." << std::endl;
    }
}

std::shared_ptr<Account> TransferTransaction::sourceAccount() {
    return _sourceAccount.lock();
}

long long TransferTransaction::amount() {
    return _amount;
}