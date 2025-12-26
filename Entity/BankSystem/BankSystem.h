#ifndef _BANK_SYSTEM_H_
#define _BANK_SYSTEM_H_

#include "../Object.h"
#include "../Account/Account.h"
#include "../Customer/Customer.h"

#include <map>
#include <memory>

using std::map;
using std::shared_ptr;
using std::string;

class BankSystem : public Object
{
private:
    map<string, shared_ptr<Customer>> _customers;
    map<string, shared_ptr<Account>> _accounts;
    shared_ptr<Customer> _currentCustomer;

public:
    string info() override;
    void addCustomer(string username, shared_ptr<Customer> customer);
    void addAccount(shared_ptr<Account> account);
    void removeAccount(string accountNumber);
    void run();
    bool login(string username, string pass);
    void logout();
    shared_ptr<Account> getAccount(string accountNumber);
};

#endif
