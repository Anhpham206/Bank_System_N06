#include "BankSystem.h"
#include "../../Business/ParserFactory/ParserFactory.h"
#include "../../Business/CheckingAccountParser/CheckingAccountParser.h"
#include "../../Business/SavingAccountParser/SavingAccountParser.h"

#include "../Account/Account.h"
#include "../Account/CheckingAccount.h"
#include "../Account/SavingAccount.h"
#include "../Customer/Customer.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>

using std::cout;
using std::string;
using std::vector;

string BankSystem::info()
{
    return "Bank: " + _name;
}

BankSystem::BankSystem(string name)
{
    _name = name;
}

void BankSystem::addCustomer(shared_ptr<Customer> customer)
{
    _customers[customer->username()] = customer;
}

void BankSystem::addAccount(shared_ptr<Account> account)
{
    _accounts[account->accountNumber()] = account;
}

void BankSystem::removeAccount(string accountNumber)
{
    // If account exists, remove reference from owner first

    auto it = _accounts.find(accountNumber);

    _accounts.erase(it);

    // Remove account file from disk
    std::filesystem::path accFile = std::filesystem::path("Data") / "Accounts" / (accountNumber + ".txt");
    std::error_code ec;
    if (std::filesystem::exists(accFile) && !std::filesystem::remove(accFile, ec))
    {
        cout << "[!] Khong the xoa file tai khoan: " << ec.message() << "\n";
    }
}

void BankSystem::run()
{
    // doc danh sach tai khoan
    std::ifstream fcustomers("Data/Customers/Customers.txt");
    if (!fcustomers)
    {
        cout << "khong mo duoc file customer\n";
    }
    string line;
    vector<string> customers;
    while (getline(fcustomers, line))
    {
        cout << line << "\n";
        customers.push_back(line);
    }
    fcustomers.close();

    ParserFactory factory;
    // doc tai khoan
    for (string name : customers)
    {
        std::ifstream fin("Data/Customers/" + name + ".txt");
        IParsable *parser = factory.create("Customer");
        getline(fin, line);
        shared_ptr<Customer> customer = std::dynamic_pointer_cast<Customer>(parser->parse(line));
        while (getline(fin, line))
        {
            customer->addAccountNumber(line);
        }
        _customers[customer->username()] = customer;
        fin.close();
        delete parser;
    }

    // doc danh sach account
    std::ifstream fAccounts("Data/Accounts/Accounts.txt");
    vector<string> accounts;
    while (getline(fAccounts, line))
    {
        accounts.push_back(line);
    }
    fAccounts.close();
    // doc account
    for (string name : accounts)
    {
        std::ifstream fin("Data/Accounts/" + name + ".txt");
        getline(fin, line);
        IParsable *parser = factory.create(line);
        getline(fin, line);
        shared_ptr<Account> account = std::dynamic_pointer_cast<Account>(parser->parse(line));

        _accounts[account->accountNumber()] = account;
        while (getline(fin, line))
        {
            account->addNotification(line);
        }
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
        return nullptr;
    }
}

shared_ptr<Customer> BankSystem::getCustomer(string username)
{
    if (_customers.find(username) != _customers.end())
    {
        return _customers[username];
    }
    else
    {
        return nullptr;
    }
}

void BankSystem::save()
{
    // Save customers list
    std::ofstream fCustomersList("Data/Customers/Customers.txt", std::ios::trunc);
    if (!fCustomersList)
    {
        cout << "Khong the mo file Customers.txt de ghi.\n";
        return;
    }

    for (auto &p : _customers)
    {
        auto cust = p.second;
        string filename = cust->getCustomerId();

        fCustomersList << filename << "\n";

        std::ofstream fout("Data/Customers/" + filename + ".txt", std::ios::trunc);
        if (!fout)
        {
            cout << "Khong the mo file customer: " << filename << "\n";
            continue;
        }

        fout << cust->getCustomerId() << ", " << cust->getName() << ", " << cust->username() << ", " << cust->password() << ", " << cust->phoneNumber() << "\n";

        for (auto &acctId : cust->getOwnedAccountIds())
            fout << acctId << "\n";
        fout.close();
    }
    fCustomersList.close();

    // Save accounts list
    std::ofstream fAccountsList("Data/Accounts/Accounts.txt", std::ios::trunc);
    if (!fAccountsList)
    {
        cout << "Khong the mo file Accounts.txt de ghi.\n";
        return;
    }

    for (auto &p : _accounts)
    {
        auto acct = p.second;
        string acctNum = acct->accountNumber();
        string type = acct->type();
        fAccountsList << acctNum << "\n";

        std::ofstream fout("Data/Accounts/" + acctNum + ".txt", std::ios::trunc);
        if (!fout)
        {
            cout << "Khong the mo file account: " << acctNum << "\n";
            continue;
        }

        if (type == "Checking Account")
        {
            auto checking = std::dynamic_pointer_cast<CheckingAccount>(acct);
            fout << "CheckingAccount\n";
            fout << checking->accountNumber() << ", " << checking->owner() << ", " << checking->balance() << ", " << checking->pin() << "\n";
        }
        else
        {
            auto saving = std::dynamic_pointer_cast<SavingAccount>(acct);
            fout << "SavingAccount\n";
            fout << saving->accountNumber() << ", " << saving->owner() << ", " << saving->balance() << ", " << saving->pin() << ", " << saving->interestRate() << "\n";
        }

        // Write notifications if any
        auto notes = acct->notifications();
        for (auto &n : notes)
            fout << n << "\n";

        fout.close();
    }
    fAccountsList.close();
}
