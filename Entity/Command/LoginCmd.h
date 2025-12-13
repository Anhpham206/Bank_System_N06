#ifndef _LOGIN_CMD_H_
#define _LOGIN_CMD_H_

#include "ICommand.h"
#include "../BankSystem/BankSystem.h"

#include <string>
#include <memory>

class LoginCmd : public ICommand
{
private:
    std::shared_ptr<BankSystem> _bankSystem;

public:
    LoginCmd(std::shared_ptr<BankSystem> bankSystem);
    void execute() override;
    ~LoginCmd() override = default;
};

#endif