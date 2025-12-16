#include "WithdrawTransaction.h"
#include <iostream>
#include <sstream>

WithdrawTransaction::WithdrawTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount)
    : Transaction(id, amount), _account(acc) {}

std::string WithdrawTransaction::info() {
    if (auto acc = _account.lock()) {
        std::stringstream ss;
        ss << "Withdrawal | ID: " << _transactionID 
           << " | Date: " << _date 
           << " | Amount: " << _amount << " VND | From: " << (acc ? "Account Number..." : "N/A");
           
        return ss.str();
    }
    return "Withdrawal | Account is no longer available.";
}

void WithdrawTransaction::execute() {
    // Khóa weak_ptr để sử dụng an toàn
    if (auto acc = _account.lock()) {
        std::cout << "Executing Withdrawal: " << _amount << " VND from Account " << (acc ? "..." : "N/A") << std::endl;
        // ... logic withdraw: acc->withdraw(_amount); ...
    } else {
        std::cerr << "Execution failed: Source Account no longer exists." << std::endl;
    }
}

std::shared_ptr<Account> WithdrawTransaction::sourceAccount() {
    return _account.lock(); 
}

long long WithdrawTransaction::amount() {
    return _amount;
}