#ifndef TRANSFER_TRANSACTION_H
#define TRANSFER_TRANSACTION_H

#include "Transaction.h"
#include <memory>

class TransferTransaction : public Transaction {
private:
    // Dùng weak_ptr cho tham chiếu không sở hữu đến Account
    std::weak_ptr<Account> _sourceAccount;
    std::weak_ptr<Account> _destinationAccount;

public:
    TransferTransaction(const std::string& id, std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount);

public:
    std::string info() override;
    void execute() override; 

    std::shared_ptr<Account> sourceAccount() override;
    long long amount() override;
};

#endif