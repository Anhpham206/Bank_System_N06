#include "BankSystemParser.h"
#include "../../Entity/BankSystem/BankSystem.h"

shared_ptr<Object> BankSystemParser::parse(string data)
{
    return make_shared<BankSystem>(data);
}