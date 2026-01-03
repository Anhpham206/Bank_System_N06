#include "LogoutCmd.h"
#include "../../Business/AppContext.h"

LogoutCmd::LogoutCmd()
{
}
bool LogoutCmd::execute()
{
    AppContext::getInstance().getBankSystem()->logout();
    return true;
}