#ifndef DEPOSIT_TRANSACTION_H
#define DEPOSIT_TRANSACTION_H

#include "Transaction.h"

class DepositTransaction : public Transaction {
private:
    Account* _account;  

public:
    DepositTransaction(const std::string& id, Account* acc, long long amount);
public:
    std::string info() override;
    void execute() override; 

    Account* sourceAccount() override;
    long long amount() override;
};

#endif
