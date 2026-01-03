#include "CheckingAccount.h"
#include <iostream>
#include <fstream>

CheckingAccount::CheckingAccount(std::string accountNumber, string owner, long long balance, string PIN)
    : Account(accountNumber, owner, balance, PIN)
{
    _type = "Checking Account";
}

std::string CheckingAccount::info()
{
    return "So tai khoan: " + _accountNumber + "\nSo du: " + std::to_string(_balance) + "\nLoai tai khoan: " + _type;
}
