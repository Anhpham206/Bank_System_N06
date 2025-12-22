#include "WithdrawTransaction.h"
#include "../Notification/WithdrawNotification.h"
#include "../Notification/Notification.h"
#include <iostream>
#include <sstream>

WithdrawTransaction::WithdrawTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount)
    : Transaction(id, amount), _account(acc) {}

std::string WithdrawTransaction::info() {
    if (auto acc = _account.lock()) {
        std::stringstream ss;
        ss << "Withdraw    | ID: " << _transactionID 
           << " | Date: " << _date 
           << " | Amount: " << _amount << " VND"
           << " | From Account: " << acc->AccountNumber();
        return ss.str();
    }
    return "Withdraw    | ID: " + _transactionID + " | Error: Source Account no longer available.";
}

void WithdrawTransaction::execute() {
    if (auto acc = _account.lock()) {
        if (acc->Balance() >= _amount) {
            acc->withdraw(_amount);
            std::cout << "Transaction " << _transactionID << ": Successfully withdrew " << _amount << " VND." << std::endl;

            auto notif = std::make_shared<WithdrawNotification>(std::static_pointer_cast<Transaction>(shared_from_this()));
            acc->addNotification(notif); 
        } else {
            std::cout << "Transaction " << _transactionID << ": Failed. Insufficient funds." << std::endl;
        }
    } else {
        std::cerr << "Execution failed: Account no longer exists." << std::endl;
    }
}

std::shared_ptr<Account> WithdrawTransaction::sourceAccount() {
    return _account.lock(); 
}

long long WithdrawTransaction::amount() {
    return _amount;
}