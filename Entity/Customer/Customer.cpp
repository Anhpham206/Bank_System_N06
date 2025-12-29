#include "Customer.h"
#include "../Account/Account.h"
#include "../BankSystem/BankSystem.h"
#include "../../Business/AppContext.h"
#include <algorithm>

#include <iostream>
#include <fstream>

Customer::Customer()
{
    _customerId = "";
    _fullName = "";
    _username = "";
    _password = "";
    _phoneNumber = "";
    _address = "";
}

Customer::Customer(std::string id, std::string name, std::string user, std::string pass, std::string phone, std::string address)
{
    _customerId = id;
    _fullName = name;
    _username = user;
    _password = pass;
    _phoneNumber = phone;
    _address = address;
}

std::string Customer::getCustomerId()
{
    return _customerId;
}

std::string Customer::getName()
{
    return _fullName;
}

bool Customer::verifyPassword(std::string pass)
{
    return _password == pass;
}

void Customer::addAccount(std::shared_ptr<Account> acct)
{

    _ownedAccount.push_back(acct->accountNumber());

    AppContext::getInstance().getBankSystem()->addAccount(acct);
}

void Customer::removeAccount(std::string acctNum)
{
    auto it = std::remove(_ownedAccount.begin(), _ownedAccount.end(), acctNum);

    if (it != _ownedAccount.end())
    {
        _ownedAccount.erase(it, _ownedAccount.end());
    }
}

std::shared_ptr<Account> Customer::getAccount(std::string acctNum)
{
    bool isOwned = false;
    for (const std::string &id : _ownedAccount)
    {
        if (id == acctNum)
        {
            isOwned = true;
            break;
        }
    }

    if (isOwned)
    {
        return AppContext::getInstance().getBankSystem()->getAccount(acctNum);
    }
    return nullptr;
}

std::string Customer::info()
{
    return "ID: " + _customerId + " | Name: " + _fullName + " | Phone: " + _phoneNumber;
}

std::string Customer::username()
{
    return _username;
}

void Customer::saveToFile()
{
    // Đặt tên file theo ID khách hàng, ví dụ: "CUST_001.txt"
    std::string filename = "CUST_" + _customerId + ".txt";
    std::ofstream outFile(filename);

    if (outFile.is_open())
    {
        outFile << _customerId << "\n";
        outFile << _fullName << "\n";
        outFile << _username << "\n";
        outFile << _password << "\n";
        outFile << _phoneNumber << "\n";
        outFile << _address << "\n";

        outFile << _ownedAccount.size() << "\n";
        for (const std::string &accId : _ownedAccount)
        {
            outFile << accId << "\n";
        }

        outFile.close();
        std::cout << "Khách hàng " << _customerId << " đã được lưu vào file\n";
    }
    else
    {
        std::cerr << "Lỗi: Không thể lưu khách hàng vào file " << filename << "\n";
    }
}

void Customer::loadAccountNumber(string accountNumber)
{
    _ownedAccount.push_back(accountNumber);
}