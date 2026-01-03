#ifndef DEPOSIT_TRANSACTION_H
#define DEPOSIT_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class DepositTransaction : public Transaction
{

public:
    DepositTransaction(std::shared_ptr<Account> acc, long long amount);

public:
    std::string info() override;
    bool execute() override;
    std::shared_ptr<Account> destAccount() override;
};

#endif