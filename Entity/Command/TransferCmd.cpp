#include "TransferCmd.h"
#include "../Transaction/TransferTransaction.h"

TransferCmd::TransferCmd(std::shared_ptr<TransferTransaction> transaction)
{
    _transaction = transaction;
}
void TransferCmd::execute()
{
    _transaction->execute();
    return;
}