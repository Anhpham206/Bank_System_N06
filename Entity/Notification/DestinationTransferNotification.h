#ifndef DESTINATION_TRANSFER_NOTIFICATION_H
#define DESTINATION_TRANSFER_NOTIFICATION_H

#include "Notification.h"
#include <memory>

class BankSystem;

class DestinationTransferNotification : public Notification
{
private:
    std::shared_ptr<BankSystem> _bank;

public:
    DestinationTransferNotification(std::shared_ptr<Transaction> transaction);

    std::string info() override;
    std::string makeMessage() override;
    std::string message() override;
};

#endif