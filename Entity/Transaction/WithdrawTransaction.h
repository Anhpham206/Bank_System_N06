#ifndef WITHDRAW_TRANSACTION_H
#define WITHDRAW_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class WithdrawTransaction : public Transaction
{
private:
    string _PIN;

public:
    WithdrawTransaction(std::shared_ptr<Account> acc, long long amount, string PIN);

public:
    std::string info() override;
    void execute() override;
};

#endif