#include "LoginCmd.h"
#include "../../Business/AppContext.h"

#include <iostream>

LoginCmd::LoginCmd()
{
}
LoginCmd::LoginCmd(string username, string password)
    : _username(username), _password(password)
{
}
bool LoginCmd::execute()
{
    auto bankSystem = AppContext::getInstance().getBankSystem();
    return bankSystem->login(_username, _password);
}