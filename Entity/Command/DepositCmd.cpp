#include "DepositCmd.h"
#include "../Transaction/DepositTransaction.h"

DepositCmd::DepositCmd(std::shared_ptr<DepositTransaction> transaction)
{
    _transaction = transaction;
}
bool DepositCmd::execute()
{
    return _transaction->execute();
}