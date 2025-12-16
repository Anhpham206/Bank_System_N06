#include "TransferTransaction.h"
#include <iostream>
#include <sstream> 

TransferTransaction::TransferTransaction(const std::string& id, std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount)
    : Transaction(id, amount), _sourceAccount(sourceAcc), _destinationAccount(destAcc) {}

std::string TransferTransaction::info() {
    // Khóa weak_ptr để sử dụng an toàn
    if (auto sourceAcc = _sourceAccount.lock()) {
        if (auto destAcc = _destinationAccount.lock()) {
            std::stringstream ss;
            ss << "Transfer | ID: " << _transactionID 
               << " | Date: " << _date 
               << " | Amount: " << _amount << " VND | From: " << "Source Acc..." 
               << " | To: " << "Dest Acc...";
            return ss.str();
        }
    }
    return "Transfer | One or both accounts are no longer available.";
}

void TransferTransaction::execute() {
    // Khóa weak_ptr để sử dụng an toàn
    if (auto sourceAcc = _sourceAccount.lock()) {
        if (auto destAcc = _destinationAccount.lock()) {
            std::cout << "Executing Transfer: " << _amount << " VND from Source to Destination Account..." << std::endl;
            // ... logic transfer: sourceAcc->withdraw(_amount); destAcc->deposit(_amount); ...
        } else {
            std::cerr << "Execution failed: Destination Account no longer exists." << std::endl;
        }
    } else {
        std::cerr << "Execution failed: Source Account no longer exists." << std::endl;
    }
}

std::shared_ptr<Account> TransferTransaction::sourceAccount() {
    return _sourceAccount.lock();
}

long long TransferTransaction::amount() {
    return _amount;
}