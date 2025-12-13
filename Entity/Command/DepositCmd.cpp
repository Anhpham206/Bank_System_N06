#include "DepositCmd.h"

DepositCmd::DepositCmd(std::shared_ptr<DepositTransaction> transaction)
{
    _transaction = transaction;
}
void DepositCmd::execute()
{
}