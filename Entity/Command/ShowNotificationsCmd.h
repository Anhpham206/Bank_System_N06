#ifndef _SHOW_NOTIFICATIONS_CMD_H_
#define _SHOW_NOTIFICATIONS_CMD_H_

#include "ICommand.h"

#include <memory>

class Account;

class ShowNotificationsCmd : public ICommand
{
private:
    std::shared_ptr<Account> _account;

public:
    ShowNotificationsCmd(std::shared_ptr<Account> account);
    void execute() override;
    ~ShowNotificationsCmd() override = default;
};

#endif