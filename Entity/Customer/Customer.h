#ifndef _CUSTOMER_H_
#define _CUSTOMER_H_

#include "../Object.h"
#include <string>
#include <vector>

class Account;

class Customer : public Object
{
private:
    std::string _customerId;
    std::string _fullName;
    std::string _username;
    std::string _password;
    std::string _phoneNumber;
    std::string _address;
    std::vector<Account *> _ownedAccount;

public:
    Customer(std::string id, std::string name, std::string user, std::string pass, std::string phone, std::string address);
    std::string getCustomerId();
    std::string getName();
    bool verifyPassword(std::string pass);
    void addAccount(Account *acct);
    void removeAccount(std::string acctNum);
    Account *getAccount(std::string acctNum);
    std::string info() override;
};

#endif
