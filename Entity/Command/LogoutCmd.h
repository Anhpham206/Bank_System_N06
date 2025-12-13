#ifndef _LOGOUT_CMD_H_
#define _LOGOUT_CMD_H_

#include "ICommand.h"
#include "../BankSystem/BankSystem.h"

#include <memory>

class LogoutCmd : public ICommand
{
private:
    std::shared_ptr<BankSystem> _bankSystem;

public:
    LogoutCmd(std::shared_ptr<BankSystem> bankSystem);
    void execute() override;
    ~LogoutCmd() override = default;
};

#endif