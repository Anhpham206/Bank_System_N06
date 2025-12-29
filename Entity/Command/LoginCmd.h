#ifndef _LOGIN_CMD_H_
#define _LOGIN_CMD_H_

#include "ICommand.h"

#include <string>
#include <memory>

class LoginCmd : public ICommand
{

public:
    LoginCmd();
    void execute() override;
    ~LoginCmd() override = default;
};

#endif