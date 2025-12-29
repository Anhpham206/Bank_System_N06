#include "TransferTransaction.h"
#include "../Notification/TransferNotification.h"
#include "../Notification/Notification.h"
#include <iostream>
#include <sstream>
#include <format>

TransferTransaction::TransferTransaction(std::shared_ptr<Account> sourceAcc, std::shared_ptr<Account> destAcc, long long amount, string PIN)
    : Transaction(sourceAcc, amount)
{
    _PIN = PIN;
    _destAccount = destAcc;
}
std::string TransferTransaction::info()
{
    std::stringstream ss;
    ss << std::format("Loai giao dich: Chuyen tien\nNguoi gui: {0}\nNguoi nhan: {1}\nLuong tien giao dich: {2}",
                      _srcAccount->accountNumber(), _destAccount->accountNumber(), _amount);
    return ss.str();
}

void TransferTransaction::execute()
{

    if (_srcAccount->verifyPIN(_PIN))
    {
        if (_srcAccount->balance() >= _amount)
        {
            _srcAccount->withdraw(_amount); // Trừ tiền nguồn
            _destAccount->deposit(_amount); // Cộng tiền đích
        }
        else
        {
            std::cout << "Tai khoan hien khong du de thuc hien giao dich!";
        }
    }
    else
    {
        std::cout << "Sai ma xac nhan!";
    }
}

std::shared_ptr<Account> TransferTransaction::destinationAccount()
{
    return _destAccount;
}
