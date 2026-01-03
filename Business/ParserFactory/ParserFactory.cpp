#include "ParserFactory.h"
#include "../BankSystemParser/BankSystemParser.h"
#include "../CustomerParser/CustomerParser.h"
#include "../SavingAccountParser/SavingAccountParser.h"
#include "../CheckingAccountParser/CheckingAccountParser.h"
#include "../TransactionParser/TransferTransactionParser.h"
#include "../TransactionParser/WithdrawTransactionParser.h"
#include "../TransactionParser/DepositTransactionParser.h"

IParsable *ParserFactory::create(string type)
{
    if (type == "BankSystem")
        return new BankSystemParser();
    if (type == "Customer")
        return new CustomerParser();
    if (type == "SavingAccount")
        return new SavingAccountParser();
    if (type == "CheckingAccount")
        return new CheckingAccountParser();
    if (type == "TransferTransaction")
        return new TransferTransactionParser();
    if (type == "WithdrawTransaction")
        return new WithdrawTransactionParser();
    if (type == "DepositTransaction")
        return new DepositTransactionParser();

    return nullptr;
}