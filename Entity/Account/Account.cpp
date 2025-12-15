#include "Account.h"
#include "Customer.h"

void Account::deposit(long long amount) {
    return;
}

void Account::withdraw(long long amount) {
    return;
}

long long Account::Balance() {
    return 0;
}

std::string Account::AccountNumber() {
    return "";
}

void Account::addNotification(Notification* notification) {
    return;
}

std::vector<Notification*> Account::Notifications() {
    return std::vector<Notification*>();
}

bool Account::verifyPIN(std::string pin) {
    return false;
}

std::string Account::info() {
    return "";
}