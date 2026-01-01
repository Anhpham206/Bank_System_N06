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
    return Account::info() + " | Type: Checking";
}

void CheckingAccount::loadFromFile(std::string numberAccount)
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

        // doc them thong bao nua

        // Dòng 2: Đọc pin
        if (std::getline(inFile, line))
        {
            _PIN = line;
        }

        inFile.close();
    }
    else
    {
        std::cout << "Lỗi: Không mở được file " << filename << ".txt\n";
    }
}
