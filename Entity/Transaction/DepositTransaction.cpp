#include "DepositTransaction.h"
#include "../Notification/DepositNotification.h"
#include <iostream>
#include <sstream> 

DepositTransaction::DepositTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount)
    : Transaction(id, amount), _account(acc) {}

std::string DepositTransaction::info() {
    if (auto acc = _account.lock()) {
        std::stringstream ss;
        ss << "Deposit     | ID: " << _transactionID 
           << " | Date: " << _date 
           << " | Amount: " << _amount << " VND"
           << " | To Account: " << acc->AccountNumber(); 
        return ss.str();
    }
    return "Deposit     | ID: " + _transactionID + " | Error: Target Account no longer available.";
}

void DepositTransaction::execute() {
    if (auto acc = _account.lock()) {
        acc->deposit(_amount); 
        std::cout << "Transaction " << _transactionID << ": Successfully deposited " << _amount << " VND." << std::endl;

        // Sử dụng shared_from_this() để truyền chính giao dịch này vào thông báo
        auto notif = std::make_shared<DepositNotification>(std::static_pointer_cast<Transaction>(shared_from_this()));
        acc->addNotification(notif);
    } else {
        std::cerr << "Execution failed: Account no longer exists." << std::endl;
    }
}

std::shared_ptr<Account> DepositTransaction::sourceAccount() {
    return nullptr; 
}

long long DepositTransaction::amount() {
    return _amount;
}