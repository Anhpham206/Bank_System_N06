#ifndef TRANSFER_TRANSACTION_H
#define TRANSFER_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class TransferTransaction : public Transaction
{
private:
    shared_ptr<Account> _destAccount;

public:
    TransferTransaction(std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount);

public:
    std::string info() override;
    bool execute() override;
    std::shared_ptr<Account> destAccount() override;
};

#endif