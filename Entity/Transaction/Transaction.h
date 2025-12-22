#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <memory>
#include "../Object.h."

class Account;

class Transaction : public Object {
protected:
    std::string _transactionID;
    std::string _date;
    long long _amount;

public:
    Transaction(const std::string& id, long long amount);
    virtual ~Transaction() = default;

public:
    std::string info() override = 0;
    virtual void execute() = 0;

    virtual std::shared_ptr<Account> sourceAccount() = 0;
    virtual long long amount() = 0;
};

#endif