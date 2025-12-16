#ifndef DEPOSIT_NOTIFICATION_H
#define DEPOSIT_NOTIFICATION_H

#include "Notification.h"

class DepositNotification : public Notification {
public:
    DepositNotification(std::shared_ptr<Transaction> transaction); //

    std::string info() override;
    std::string makeMessage() override;
    std::string message() override;
};

#endif