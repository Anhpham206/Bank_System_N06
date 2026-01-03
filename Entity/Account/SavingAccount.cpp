#include "SavingAccount.h"
#include <fstream>
#include <iostream>

SavingAccount::SavingAccount(std::string accountNumber, string owner, long long balance, string PIN, double rate)
    : Account(accountNumber, owner, balance, PIN)
{
    _interestRate = rate;
    _type = "Saving Account";
}

void SavingAccount::addInterest()
{
    _balance += _balance * _interestRate;
}

std::string SavingAccount::info()
{
    return "So tai khoan: " + _accountNumber + "\nSo du: " + std::to_string(_balance) + "\nLoai tai khoan: " + _type + "\nLai suat: " + std::to_string(_interestRate * 100) + "%";
}

double SavingAccount::interestRate() const
{
    return _interestRate;
}
