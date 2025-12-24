#ifndef _SAVINGACCOUNTDECORATOR_H_
#define _SAVINGACCOUNTDECORATOR_H_

#include "SavingAccount.h"

class SavingAccountDecorator : public SavingAccount {
public:
    // [ĐÃ THÊM] Constructer chyển tiếp
    SavingAccountDecorator(std::string accountNumber, Customer* owner, double rate);
    virtual void addInterest() = 0;
    virtual std::string info() = 0;
};

#endif
