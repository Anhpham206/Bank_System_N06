#include "AppContext.h"
#include "IParsable.h"
#include "ParserFactory/ParserFactory.h"

#include <memory>
#include <string>

void AppContext::initialize(const std::string &bankName)
{
    if (_bankSystem == nullptr)
    {
        ParserFactory factory;
        IParsable *parser = factory.create("BankSystem");
        auto bank = parser->parse(bankName);
        _bankSystem = std::dynamic_pointer_cast<BankSystem>(bank);
    }
}

std::shared_ptr<BankSystem> AppContext::getBankSystem()
{
    if (_bankSystem == nullptr)
    {
        return nullptr;
    }
    return _bankSystem;
}
