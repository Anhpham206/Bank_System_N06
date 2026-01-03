#ifndef _BANK_SYSTEM_H_
#define _BANK_SYSTEM_H_

#include "../Object.h"

#include <map>
#include <memory>

class Account;
class Customer;

using std::map;
using std::shared_ptr;
using std::string;

class BankSystem : public Object
{
private:
    string _name;
    map<string, shared_ptr<Customer>> _customers;
    map<string, shared_ptr<Account>> _accounts;
    shared_ptr<Customer> _currentCustomer;

public:
    BankSystem() {};
    BankSystem(string name);

public:
    void addCustomer(shared_ptr<Customer> customer);
    void addAccount(shared_ptr<Account> account);
    void removeAccount(string accountNumber);
    void run();
    void save();
    bool login(string username, string pass);
    void logout();
    shared_ptr<Account> getAccount(string accountNumber);
    shared_ptr<Customer> currentCustomer();
    string info() override;
    shared_ptr<Customer> getCustomer(string username);

    void check();
};

#endif
