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
protected: // [ĐÃ SỬA] Để class con (Saving và Checking) có thể thay đổi dữ liệu
    std::string _accountNumber;
    long long _balance;
    string _owner;
    string _type;
    std::vector<string> _notifications;
    std::string _PIN;

public:
    // [ĐÃ THÊM] Constructor để class con gọi
    Account(std::string accountNumber, string owner, long long balance, string PIN);

    virtual ~Account() = default; // Nên có destructor ảo

    void deposit(long long amount);
    void withdraw(long long amount);
    long long balance();
    std::string accountNumber();

    void addNotification(string notification);

    std::vector<string> notifications();

    bool verifyPIN(std::string pin);

    virtual void loadFromFile(std::string numberAccount) = 0;
    std::string info() override;

    string type();
};

#endif
