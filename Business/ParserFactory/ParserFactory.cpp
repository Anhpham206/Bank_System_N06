#include "ParserFactory.h"
#include "../BankSystemParser/BankSystemParser.h"
#include "../CustomerParser/CustomerParser.h"
#include "../SavingAccountParser/SavingAccountParser.h"
#include "../CheckingAccountParser/CheckingAccountParser.h"
#include "../TransactionParser/TransactionParser.h"

IParsable* ParserFactory::create(string type) {
    if (type == "BankSystem") return new BankSystemParser();
    if (type == "Customer") return new CustomerParser();
    if (type == "SavingAccount") return new SavingAccountParser();
    if (type == "CheckingAccount") return new CheckingAccountParser();
    if (type == "Transaction") return new TransactionParser();
    
    return nullptr;
}