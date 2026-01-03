#include "ShowNotificationsCmd.h"
#include "../Notification/Notification.h"
#include "../Account/Account.h"

#include <vector>
#include <iostream>

using std::vector;

ShowNotificationsCmd::ShowNotificationsCmd(std::shared_ptr<Account> account)
{
    _account = account;
}
bool ShowNotificationsCmd::execute()
{
    vector<string> list = _account->notifications();
    if (list.empty())
    {
        std::cout << "Khong co thong bao!\n";
        return false;
    }
    for (string notification : list)
    {
        std::cout << notification << "\n";
    }
    return true;
}