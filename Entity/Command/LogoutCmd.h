#ifndef _LOGOUT_CMD_H_
#define _LOGOUT_CMD_H_

#include "ICommand.h"

#include <memory>

class LogoutCmd : public ICommand
{
public:
    LogoutCmd();
    bool execute() override;
    ~LogoutCmd() override = default;
};

#endif