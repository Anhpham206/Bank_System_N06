#include "Customer.h"
#include "../Account/Account.h"
#include <algorithm>

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

void Customer::addAccount(Account *acct)
{
    if (acct)
    {
        _ownedAccount.push_back(acct);
    }
}

void Customer::removeAccount(std::string acctNum)
{
    auto it = std::remove_if(_ownedAccount.begin(), _ownedAccount.end(),
                             [&acctNum](Account *acc)
                             {
                                 return acc->AccountNumber() == acctNum;
                             });

    if (it != _ownedAccount.end())
    {
        _ownedAccount.erase(it, _ownedAccount.end());
    }
}

Account *Customer::getAccount(std::string acctNum)
{
    for (Account *acc : _ownedAccount)
    {
        if (acc->AccountNumber() == acctNum)
        {
            return acc;
        }
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
