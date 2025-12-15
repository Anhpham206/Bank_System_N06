#ifndef SAVINGACCOUNT_H
#define SAVINGACCOUNT_H

#include "Account.h"

class SavingAccount : public Account {
private:
    float _interestRate;

public:
    SavingAccount(std::string accountNumber, Customer* owner, double rate);
    void loadFromFile(std::string numberAccount) override;
};

#endif