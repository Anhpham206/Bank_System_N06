#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../Object.h"
#include "../../Business/Transaction/Transaction.h"
#include <string>
#include <memory>

class Notification : public Object {
protected:
    std::shared_ptr<Transaction> _transaction; //
    std::string _time;

public:
    Notification(std::shared_ptr<Transaction> transaction); //
    virtual ~Notification() = default;

    std::string info() override = 0;
    virtual std::string makeMessage() = 0;
    virtual std::string message() = 0;

    void displayInfo(); 
};

#endif