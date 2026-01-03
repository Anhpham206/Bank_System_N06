#ifndef _CHECKINGACCOUNT_H_
#define _CHECKINGACCOUNT_H_

#include "Account.h"

class CheckingAccount : public Account
{
public:
    CheckingAccount(std::string accountNumber, string owner, long long balance, string PIN);
    std::string info() override;
};

#endif
