#ifndef TRANSFER_NOTIFICATION_H
#define TRANSFER_NOTIFICATION_H

#include "Notification.h"

class TransferNotification : public Notification {
public:
    TransferNotification(std::shared_ptr<Transaction> transaction);

    std::string info() override;
    std::string makeMessage() override;
    std::string message() override;
};

#endif