#include "Account.h"
#include "../Customer/Customer.h"
#include "../Notification/Notification.h" // Cần include để nhận diện kiểu dữ liệu shared_ptr

void Account::deposit(long long amount) {
    _balance += amount; // Cập nhật logic thực tế thay vì return trống
}

void Account::withdraw(long long amount) {
    if (_balance >= amount) {
        _balance -= amount; // Cập nhật logic thực tế thay vì return trống
    }
}

long long Account::Balance() {
    return _balance;
}

std::string Account::AccountNumber() {
    return _accountNumber;
}

// [ĐÃ SỬA] Sử dụng std::shared_ptr<Notification>
void Account::addNotification(std::shared_ptr<Notification> notification) {
    if (notification) {
        _notifications.push_back(notification);
    }
}

// [ĐÃ SỬA] Trả về vector chứa shared_ptr
std::vector<std::shared_ptr<Notification>> Account::Notifications() {
    return _notifications;
}

bool Account::verifyPIN(std::string pin) {
    return _PIN == pin;
}

std::string Account::info() {
    return "Account No: " + _accountNumber + " | Balance: " + std::to_string(_balance);
}