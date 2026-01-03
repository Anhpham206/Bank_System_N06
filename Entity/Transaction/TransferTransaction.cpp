#include "TransferTransaction.h"
#include "../Notification/SourceTransferNotification.h"
#include "../Notification/Notification.h"
#include "../Notification/DestinationTransferNotification.h"
#include "../Command/DisplayInfoCmd.h"
#include "../Notification/SourceTransferNotification.h"
#include "../Account/Account.h"
#include <iostream>
#include <sstream>
#include <format>

TransferTransaction::TransferTransaction(std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount)
    : Transaction(sourceAcc, amount)
{
    _destAccount = destAcc;
}
std::string TransferTransaction::info()
{
    std::stringstream ss;
    ss << std::format("Loai giao dich: Chuyen tien\nNguoi gui: {0}\nNguoi nhan: {1}\nLuong tien giao dich: {2}",
                      _srcAccount->accountNumber(), _destAccount->accountNumber(), _amount);
    return ss.str();
}

bool TransferTransaction::execute()
{

    if (_srcAccount->balance() >= _amount)
    {
        _srcAccount->withdraw(_amount); // Trừ tiền nguồn
        _destAccount->deposit(_amount); // Cộng tiền đích
        std::shared_ptr<SourceTransferNotification> srcNotification = std::make_shared<SourceTransferNotification>(shared_from_this());
        _srcAccount->addNotification(srcNotification->message());
        std::shared_ptr<DestinationTransferNotification> destNotification = std::make_shared<DestinationTransferNotification>(shared_from_this());
        _destAccount->addNotification(destNotification->message());
        DisplayInfoCmd displaySrcCmd(srcNotification);
        displaySrcCmd.execute();
        return true;
    }
    else
    {
        std::cout << "Tai khoan hien khong du de thuc hien giao dich!";
        return false;
    }
}
std::shared_ptr<Account> TransferTransaction::destAccount()
{
    return _destAccount;
}