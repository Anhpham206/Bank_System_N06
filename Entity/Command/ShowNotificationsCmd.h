#ifndef _SHOW_NOTIFICATIONS_CMD_H_
#define _SHOW_NOTIFICATIONS_CMD_H_

#include "ICommand.h"
#include "../Account/Account.h"


#include <memory>



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