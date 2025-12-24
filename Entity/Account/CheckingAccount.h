#ifndef _CHECKINGACCOUNT_H_
#define _CHECKINGACCOUNT_H_

#include "Account.h"

class CheckingAccount : public Account {
public:
    CheckingAccount(std::string accountNumber, Customer* owner);
    std::string info() override;
    void loadFromFile(std::string numberAccount) override;
};

#endif
