#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Object.h"
#include <string>
#include <vector>

class Customer;
class Notification;

class Account : public Object
{
private:
    std::string _accountNumber;
    long long _balance;
    Customer *_owner;
    std::vector<Notification *> _notifications;
    std::string _PIN;

public:
    void deposit(long long amount);
    void withdraw(long long amount);
    long long balance();
    std::string accountNumber();
    void addNotification(Notification *notification);
    std::vector<Notification *> notifications();
    bool verifyPIN(std::string pin);
    virtual void loadFromFile(std::string numberAccount) = 0;
    std::string info() override;
};

#endif