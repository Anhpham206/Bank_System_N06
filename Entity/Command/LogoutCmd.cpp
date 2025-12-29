#include "LogoutCmd.h"
#include "../../Business/AppContext.h"

LogoutCmd::LogoutCmd()
{
}
void LogoutCmd::execute()
{
    AppContext::getInstance().getBankSystem()->logout();
    return;
}