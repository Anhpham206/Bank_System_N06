#include "SourceTransferNotification.h"
#include "../../Business/AppContext.h"
#include "../Customer/Customer.h"
#include "../Account/Account.h"
#include <sstream>

SourceTransferNotification::SourceTransferNotification(std::shared_ptr<Transaction> transaction)
    : Notification(transaction)
{
    _bank = AppContext::getInstance().getBankSystem();
}

std::string SourceTransferNotification::makeMessage()
{
    long long amount = _transaction ? _transaction->amount() : 0;
    std::stringstream ss;
    ss << "Chuyen tien thanh cong " << amount << " VND den " << _bank->getCustomer(_transaction->destAccount()->owner())->getName() << ".";
    return ss.str();
}

std::string SourceTransferNotification::message()
{
    return _time + ": " + makeMessage();
}

std::string SourceTransferNotification::info()
{
    std::stringstream ss;
    ss << "--------- THONG BAO ---------\n";
    ss << "Thoi gian: " << _time << "\n";
    ss << "Noi dung : " << makeMessage() << "\n";
    ss << "-----------------------------\n";
    return ss.str();
}