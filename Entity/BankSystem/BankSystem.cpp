#include "BankSystem.h"
#include "../Business/ParserFactory/ParserFactory.h"
#include "../Business/CheckingAccountParser/CheckingAccountParser.h"
#include "../Business/SavingAccountParser/SavingAccountParser.h"

#include <iostream>
#include <fstream>
#include <vector>

using std::cout;
using std::string;
using std::vector;

string BankSystem::info()
{
    return "Bank System info: do something...";
}

void BankSystem::addCustomer(shared_ptr<Customer> customer)
{
    _customers[customer->username()] = customer;
}

void BankSystem::addAccount(shared_ptr<Account> account)
{
    _accounts[account->AccountNumber()] = account;
}

void BankSystem::removeAccount(string accountNumber)
{
    _accounts.erase(accountNumber);
}

void BankSystem::run()
{
    // doc danh sach tai khoan
    std::ifstream fcustomers("../../Data/Customers/Customers.txt");
    string line;
    vector<string> customers;
    while (getline(fcustomers, line))
    {
        customers.push_back(line);
    }
    fcustomers.close();

    ParserFactory factory;
    // doc tai khoan
    for (string name : customers)
    {
        std::ifstream fin("../../Data/Customers/" + name + ".txt");
        IParsable *parser = factory.create("Customer");
        getline(fin, line);
        shared_ptr<Customer> customer = std::dynamic_pointer_cast<Customer>(parser->parse(line));
        _customers[customer->username()] = customer;
        fin.close();
        delete parser;
    }

    // doc danh sach account
    std::ifstream fAccounts("../../Data/Accounts/Accounts.txt");
    vector<string> accounts;
    while (getline(fAccounts, line))
    {
        accounts.push_back(line);
    }
    // doc account
    for (string name : accounts)
    {
        std::ifstream fin("../../Data/Accounts/" + name + ".txt");
        getline(fin, line);
        IParsable *parser = factory.create(line);
        getline(fin, line);
        shared_ptr<Account> account = std::dynamic_pointer_cast<Account>(parser->parse(line));
        _accounts[account->AccountNumber()] = account;
        fin.close();
        delete parser;
    }
}

shared_ptr<Customer> BankSystem::currentCustomer()
{
    return _currentCustomer;
}

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
