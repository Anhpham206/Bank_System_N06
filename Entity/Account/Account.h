#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "../Object.h"
#include <string>
#include <vector>
#include <memory> // [ĐÃ THÊM] Để dùng shared_ptr

class Customer;
class Notification; // Forward declaration

class Account : public Object {
private:
    std::string _accountNumber;
    long long _balance;
    Customer* _owner;
    // [ĐÃ SỬA] Dùng shared_ptr để quản lý danh sách thông báo
    std::vector<std::shared_ptr<Notification>> _notifications; 
    std::string _PIN;

public:
    virtual ~Account() = default; // Nên có destructor ảo

    void deposit(long long amount);
    void withdraw(long long amount);
    long long Balance();
    std::string AccountNumber();

    // [ĐÃ SỬA] Nhận vào shared_ptr
    void addNotification(std::shared_ptr<Notification> notification);
    
    // [ĐÃ SỬA] Trả về vector chứa shared_ptr
    std::vector<std::shared_ptr<Notification>> Notifications();
    
    bool verifyPIN(std::string pin);
    virtual void loadFromFile(std::string numberAccount) = 0;
    std::string info() override;
};

#endif