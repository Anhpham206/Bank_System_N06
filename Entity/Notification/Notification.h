#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../Object.h"
#include "../Transaction/Transaction.h"
#include <string>
#include <memory>
#include <iostream>

class Notification : public Object
{
protected:
    std::shared_ptr<Transaction> _transaction;
    std::string _time;

public:
    Notification(std::shared_ptr<Transaction> transaction);
    virtual ~Notification() = default;

    // Hàm trả về thông tin đầy đủ (gồm cả thời gian)
    std::string info() override = 0;

    // Hàm tạo nội dung thông báo
    virtual std::string makeMessage() = 0;

    // Hàm trả về nội dung thông báo (để lưu vào Account)
    virtual std::string message() = 0;
};

#endif