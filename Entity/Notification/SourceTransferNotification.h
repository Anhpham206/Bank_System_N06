#ifndef SOURCE_TRANSFER_NOTIFICATION_H
#define SOURCE_TRANSFER_NOTIFICATION_H

#include "Notification.h"
#include <memory>

class BankSystem;

class SourceTransferNotification : public Notification
{
private:
    std::shared_ptr<BankSystem> _bank;

public:
    SourceTransferNotification(std::shared_ptr<Transaction> transaction);

    std::string info() override;
    std::string makeMessage() override;
    std::string message() override;
};

#endif