#ifndef WITHDRAW_NOTIFICATION_H
#define WITHDRAW_NOTIFICATION_H

#include "Notification.h"

class WithdrawNotification : public Notification {
public:
    WithdrawNotification(std::shared_ptr<Transaction> transaction);

    std::string info() override;
    std::string makeMessage() override;
    std::string message() override;
};

#endif