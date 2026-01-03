#include "TransferCmd.h"
#include "../Transaction/TransferTransaction.h"

#include <iostream>

TransferCmd::TransferCmd(std::shared_ptr<TransferTransaction> transaction)
{
    _transaction = transaction;
}
bool TransferCmd::execute()
{
    bool result = _transaction->execute();
    return result;
}