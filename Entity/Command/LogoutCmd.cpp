#include "LogoutCmd.h"

LogoutCmd::LogoutCmd(std::shared_ptr<BankSystem> bankSystem)
{
    _bankSystem = bankSystem;
}
void LogoutCmd::execute()
{
    _bankSystem->logout();
    return;
}