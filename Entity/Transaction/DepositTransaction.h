#ifndef DEPOSIT_TRANSACTION_H
#define DEPOSIT_TRANSACTION_H

#include "Transaction.h"
#include <memory> // Cần thiết cho std::weak_ptr

class DepositTransaction : public Transaction
{

public:
    DepositTransaction(std::shared_ptr<Account> acc, long long amount);

public:
    std::string info() override;
    void execute() override;
};

#endif