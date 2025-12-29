#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <memory>
#include "../Object.h."
#include "../Account/Account.h"

using std::shared_ptr;

class Transaction : public Object, public std::enable_shared_from_this<Transaction>
{
protected:
    std::shared_ptr<Account> _srcAccount;
    long long _amount;

public:
    Transaction(shared_ptr<Account> srcAccount, long long amount);
    virtual ~Transaction() = default;

public:
    virtual std::string info() = 0;
    virtual void execute() = 0;

    shared_ptr<Account> sourceAccount();
    long long amount();
};

#endif