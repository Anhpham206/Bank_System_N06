#include "Notification.h"
#include <iostream>

Notification::Notification(std::shared_ptr<Transaction> transaction) //
    : _transaction(transaction) {
    this->_time = "YYYY-MM-DD HH:MM:SS"; 
}

void Notification::displayInfo() {
    // Gọi phương thức message() đa hình để lấy nội dung
    std::cout << "--- NOTIFICATION ---" << std::endl;
    std::cout << "Time: " << _time << std::endl;
    std::cout << "Message: " << message() << std::endl;
    std::cout << "--------------------" << std::endl;
}