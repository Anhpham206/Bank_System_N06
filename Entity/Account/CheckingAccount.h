#ifndef CHECKINGACCOUNT_H
#define CHECKINGACCOUNT_H

#include "Account.h"

class CheckingAccount : public Account {
public:
    CheckingAccount(std::string accountNumber, Customer* owner);
    std::string info() override;
    void loadFromFile(std::string numberAccount) override;
};

#endif