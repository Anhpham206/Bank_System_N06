#include "Customer.h"
#include "Account/Account.h"

Customer::Customer(std::string id, std::string name, std::string user, std::string pass, std::string phone, std::string address) {
    return;
}

std::string Customer::getCustomerId() {
    return "";
}

std::string Customer::getName() {
    return "";
}

bool Customer::verifyPassword(std::string pass) {
    return false;
}

void Customer::addAccount(Account* acct) {
    return;
}

void Customer::removeAccount(std::string acctNum) {
    return;
}

Account* Customer::getAccount(std::string acctNum) {
    return nullptr;
}

std::string Customer::info() {
    return "";
}