#ifndef _SAVINGACCOUNT_H_
#define _SAVINGACCOUNT_H_

#include "Account.h"

class SavingAccount : public Account {
private:
    double _interestRate;

public:
    SavingAccount(std::string accountNumber, Customer* owner, double rate);
    void loadFromFile(std::string numberAccount) override;
    std::string info() override; // Override thêm info nếu cần hiển thị lãi suất
};

#endif
