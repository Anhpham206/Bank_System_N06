#ifndef SAVINGACCOUNTDECORATOR_H
#define SAVINGACCOUNTDECORATOR_H

#include "SavingAccount.h"

class SavingAccountDecorator : public SavingAccount {
public:
    virtual void addInterest() = 0;
    virtual std::string info() = 0;
};

#endif