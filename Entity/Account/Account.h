#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include "../Object.h"
#include <string>
#include <vector>
#include <memory>

class Customer;
class Notification; // Forward declaration

class Account : public Object
{
protected:
    std::string _accountNumber;
    long long _balance;
    string _owner;
    string _type;
    std::vector<string> _notifications;
    std::string _PIN;

public:
    Account(std::string accountNumber, string owner, long long balance, string PIN);

    virtual ~Account() = default; // Nên có destructor ảo

    void deposit(long long amount);
    void withdraw(long long amount);
    long long balance();
    std::string accountNumber();

    void addNotification(string notification);

    std::vector<string> notifications();

    bool verifyPIN(std::string pin);

    // Getters used for persistence
    std::string pin() const;

    virtual std::string info() = 0;
    string owner();

    string type();
};

#endif
