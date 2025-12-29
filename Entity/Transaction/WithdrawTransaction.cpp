#include "WithdrawTransaction.h"
#include "../Notification/WithdrawNotification.h"
#include "../Notification/Notification.h"
#include <iostream>
#include <sstream>
#include <format>

WithdrawTransaction::WithdrawTransaction(std::shared_ptr<Account> acc, long long amount, string PIN)
    : Transaction(acc, amount)
{
    _PIN = PIN;
}

std::string WithdrawTransaction::info()
{
    std::stringstream ss;
    ss << std::format("Loai giao dich: Rut tien\nLuong tien gia dich:{0}", _amount);
    return ss.str();
}

void WithdrawTransaction::execute()
{
    if (_srcAccount->verifyPIN(_PIN))
    {
        if (_srcAccount->balance() >= _amount)
        {
            _srcAccount->withdraw(_amount);
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
