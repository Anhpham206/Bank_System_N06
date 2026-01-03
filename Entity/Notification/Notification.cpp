#include "Notification.h"
#include <iostream>
#include <ctime>
#include <vector>

Notification::Notification(std::shared_ptr<Transaction> transaction)
    : _transaction(transaction)
{

    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);

    // Định dạng: %H:%M:%S (Giờ:Phút:Giây), %a (Thứ), %d (Ngày), %m (Tháng), %Y (Năm)
    strftime(buf, sizeof(buf), "%H:%M:%S, %A %d/%m/%Y", &tstruct);

    this->_time = std::string(buf);
}
