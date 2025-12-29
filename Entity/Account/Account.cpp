#include "Account.h"
#include "../Customer/Customer.h"
#include "../Notification/Notification.h"

// Implement Constructor
Account::Account(std::string accountNumber, string owner, long long balance, string PIN)
{
    _accountNumber = accountNumber;
    _owner = owner;
    _balance = balance;
    _PIN = PIN;
}

void Account::deposit(long long amount)
{
    if (amount > 0)
    {
        _balance += amount;
    }
}

void Account::withdraw(long long amount)
{
    if (amount > 0 && _balance >= amount)
    {
        _balance -= amount;
    }
}

long long Account::balance()
{
    return _balance;
}

std::string Account::accountNumber()
{
    return _accountNumber;
}

void Account::addNotification(string notification)
{
    _notifications.push_back(notification);
}

std::vector<string> Account::notifications()
{
    return _notifications;
}

bool Account::verifyPIN(std::string pin)
{
    return _PIN == pin;
}

std::string Account::info()
{
    return "Account No: " + _accountNumber + " | Balance: " + std::to_string(_balance);
}
