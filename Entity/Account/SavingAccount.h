#ifndef _SAVINGACCOUNT_H_
#define _SAVINGACCOUNT_H_

#include "Account.h"

class SavingAccount : public Account
{
private:
    double _interestRate;

public:
    SavingAccount(std::string accountNumber, string owner, long long balance, string PIN, double rate);
    void loadFromFile(std::string numberAccount) override;
    void addInterest();
    std::string info() override; // Override thêm info nếu cần hiển thị lãi suất
};

#endif
