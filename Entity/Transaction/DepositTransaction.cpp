#include "DepositTransaction.h"
#include <iostream>
#include <sstream> 

DepositTransaction::DepositTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount)
    : Transaction(id, amount), _account(acc) {}

std::string DepositTransaction::info() {
    // Khóa weak_ptr để sử dụng an toàn
    if (auto acc = _account.lock()) {
        std::stringstream ss;
        ss << "Deposit | ID: " << _transactionID 
           << " | Date: " << _date 
           << " | Amount: " << _amount << " VND | To: " << (acc ? "Account Number..." : "N/A"); 
           
        return ss.str();
    }
    return "Deposit | Account is no longer available.";
}

void DepositTransaction::execute() {
    // Khóa weak_ptr để sử dụng an toàn
    if (auto acc = _account.lock()) {
        std::cout << "Executing Deposit: " << _amount << " VND to Account " << (acc ? "..." : "N/A") << std::endl;
        // ... logic deposit: acc->deposit(_amount); ...
    } else {
        std::cerr << "Execution failed: Target Account no longer exists." << std::endl;
    }
}

std::shared_ptr<Account> DepositTransaction::sourceAccount() {
    return nullptr; 
}

long long DepositTransaction::amount() {
    return _amount;
}