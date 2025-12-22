#ifndef WITHDRAW_TRANSACTION_H
#define WITHDRAW_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class WithdrawTransaction : public Transaction {
private:
    // Dùng weak_ptr cho tham chiếu không sở hữu đến Account
    std::weak_ptr<Account> _account;

public:
    WithdrawTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount);

public:
    std::string info() override;
    void execute() override; 

    std::shared_ptr<Account> sourceAccount() override;
    long long amount() override;
};

#endif