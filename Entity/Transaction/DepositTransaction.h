#ifndef DEPOSIT_TRANSACTION_H
#define DEPOSIT_TRANSACTION_H

#include "Transaction.h"
#include <memory> // Cần thiết cho std::weak_ptr

class DepositTransaction : public Transaction {
private:
    // Dùng weak_ptr cho tham chiếu không sở hữu đến Account
    std::weak_ptr<Account> _account;  

public:
    DepositTransaction(const std::string& id, std::shared_ptr<Account> acc, long long amount);

public:
    std::string info() override;
    void execute() override; 

    std::shared_ptr<Account> sourceAccount() override;
    long long amount() override;
};

#endif