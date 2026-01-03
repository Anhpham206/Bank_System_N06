#include "DestinationTransferNotification.h"
#include "../../Business/AppContext.h"
#include "../Customer/Customer.h"
#include "../Account/Account.h"
#include <sstream>

DestinationTransferNotification::DestinationTransferNotification(std::shared_ptr<Transaction> transaction)
    : Notification(transaction)
{
    _bank = AppContext::getInstance().getBankSystem();
}

std::string DestinationTransferNotification::makeMessage()
{
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Nhan tien " << amount << " VND tu " << _bank->getCustomer(_transaction->sourceAccount()->owner())->getName() << ".";
    return ss.str();
}

std::string DestinationTransferNotification::message()
{
    return _time + ": " + makeMessage();
}

std::string DestinationTransferNotification::info()
{
    std::stringstream ss;
    ss << "--------- THONG BAO ---------\n";
    ss << "Thoi gian: " << _time << "\n";
    ss << "Noi dung : " << makeMessage() << "\n";
    ss << "-----------------------------\n";
    return ss.str();
}