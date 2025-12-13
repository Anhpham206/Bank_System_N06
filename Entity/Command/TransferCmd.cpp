#include "TransferCmd.h"

TransferCmd::TransferCmd(std::shared_ptr<TransferTransaction> transaction)
{
    _transaction = transaction;
}
void execute()
{
    return;
}