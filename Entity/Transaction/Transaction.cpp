#include "Transaction.h"

Transaction::Transaction(shared_ptr<Account> srcAccount, long long amount)
{
    _srcAccount = srcAccount;
    _amount = amount;
}

shared_ptr<Account> Transaction::sourceAccount()
{
    return _srcAccount;
}

long long Transaction::amount()
{
    return _amount;
}