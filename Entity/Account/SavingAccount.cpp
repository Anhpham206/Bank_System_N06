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
    return Account::info() + " | Type: Saving | Rate: " + std::to_string(_interestRate);
}

void SavingAccount::loadFromFile(std::string numberAccount)
{
    std::string filename = numberAccount + ".txt";
    std::ifstream inFile(filename);

    if (inFile.is_open())
    {
        std::string line;

        // Dòng 1: Đọc balance
        if (std::getline(inFile, line))
        {
            try
            {
                _balance = std::stoll(line);
            }
            catch (...)
            {
                _balance = 0;
            }
        }

        // Dòng 2: Đọc pin
        if (std::getline(inFile, line))
        {
            _PIN = line;
        }

        // Dòng 3: Đọc interest rate
        if (std::getline(inFile, line))
        {
            try
            {
                _interestRate = std::stod(line);
            }
            catch (...)
            {
                _interestRate = 0.0;
            }
        }

        inFile.close();
    }
    else
    {
        std::cout << "Lỗi: Không mở được file " << filename << ".txt\n";
    }
}
