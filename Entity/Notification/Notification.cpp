#include "Notification.h"
#include <iostream>
#include <ctime>

Notification::Notification(std::shared_ptr<Transaction> transaction)
    : _transaction(transaction) {
    time_t now = time(0);
    char* dt = ctime(&now);
    this->_time = std::string(dt);
    if (!this->_time.empty() && this->_time.back() == '\n') _time.pop_back();
}

void Notification::displayInfo() {
    std::cout << "========= THÔNG BÁO =========" << std::endl;
    std::cout << "Thời gian: " << _time << std::endl;
    std::cout << "Nội dung: " << message() << std::endl;
    std::cout << "=============================" << std::endl;
}