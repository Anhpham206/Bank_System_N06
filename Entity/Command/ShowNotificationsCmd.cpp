#include "ShowNotificationsCmd.h"
#include "../Notification/Notification.h"

#include <vector>
#include <iostream>

using std::vector;

ShowNotificationsCmd::ShowNotificationsCmd(std::shared_ptr<Account> account)
{
    _account = account;
}
void ShowNotificationsCmd::execute()
{
    vector<std::shared_ptr<Notification>> list = _account->notifications();
    for (std::shared_ptr<Notification> notification : list)
    {
        std::cout << notification->message() << "\n";
    }
    return;
}