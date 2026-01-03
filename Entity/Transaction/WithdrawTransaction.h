#ifndef WITHDRAW_TRANSACTION_H
#define WITHDRAW_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class WithdrawTransaction : public Transaction
{

public:
    WithdrawTransaction(std::shared_ptr<Account> acc, long long amount);

public:
    std::string info() override;
    bool execute() override;
    std::shared_ptr<Account> destAccount() override;
};

#endif