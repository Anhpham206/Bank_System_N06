#include "BankSystem.h"

#include <iostream>

using std::cout;
using std::string;

string BankSystem::info()
{
    return "Bank System info: do something...";
}
void BankSystem::addCustomer(string username, shared_ptr<Customer> customer)
{
    _customers[username] = customer;
}
void BankSystem::addAccount(shared_ptr<Account> account)
{
    _accounts[account->AccountNumber()] = account;
}
void BankSystem::removeAccount(string accountNumber)
{
    _accounts.erase(accountNumber);
}
void run();

bool BankSystem::login(string username, string pass)
{

    if (_customers.find(username) != _customers.end())
    {
        shared_ptr<Customer> currCustomer = _customers[username];
        if (currCustomer->verifyPassword(pass))
        {
            _currentCustomer = currCustomer;
            cout << "Đăng nhập thành công!\n";
            return true;
        }
        else
        {
            cout << "Sai mật khẩu!\n";
            return false;
        }
    }
    else
    {
        cout << "Tài khoản không tồn tại!\n";
        return false;
    }
}
void BankSystem::logout()
{
    _currentCustomer = nullptr;
}
shared_ptr<Account> BankSystem::getAccount(string accountNumber)
{
    if (_accounts.find(accountNumber) != _accounts.end())
    {
        return _accounts[accountNumber];
    }
    else
    {
        cout << "Tài khoản không tồn tại!\n";
        return nullptr;
    }
}
