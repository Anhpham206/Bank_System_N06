#include "Account.h"
#include "../Customer/Customer.h"
#include "../Notification/Notification.h"

// Implement Constructor
Account::Account(std::string accountNumber, Customer* owner, long long balance) {
    _accountNumber = accountNumber;
    _owner = owner;
    _balance = balance;
    _PIN = "123456"; // Default PIN
}

void Account::deposit(long long amount) {
    if (amount > 0) {
        _balance += amount;
    }
}

void Account::withdraw(long long amount) {
    if (amount > 0 && _balance >= amount) {
        _balance -= amount;
    }
}

long long Account::Balance() {
    return _balance;
}

std::string Account::AccountNumber() {
    return _accountNumber;
}

void Account::addNotification(std::shared_ptr<Notification> notification) {
    if (notification) {
        _notifications.push_back(notification);
    }
}

std::vector<std::shared_ptr<Notification>> Account::Notifications() {
    return _notifications;
}

bool Account::verifyPIN(std::string pin) {
    return _PIN == pin;
}

void Account::setPIN(std::string pin) {
    _PIN = pin;
}

std::string Account::info() {
    return "Account No: " + _accountNumber + " | Balance: " + std::to_string(_balance);
}
