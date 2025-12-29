#ifndef TRANSFER_TRANSACTION_H
#define TRANSFER_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class TransferTransaction : public Transaction
{
private:
    string _PIN;
    shared_ptr<Account> _destAccount;

public:
    TransferTransaction(std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount, string PIN);

public:
    std::string info() override;
    void execute() override;
    shared_ptr<Account> destinationAccount();
};

#endif