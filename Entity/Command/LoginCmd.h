#ifndef _LOGIN_CMD_H_
#define _LOGIN_CMD_H_

#include "ICommand.h"

#include <string>
#include <memory>

using std::string;

class LoginCmd : public ICommand
{
private:
    string _username;
    string _password;

public:
    LoginCmd();
    LoginCmd(string username, string password);

public:
    bool execute() override;
    ~LoginCmd() override = default;
};

#endif