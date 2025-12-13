#include "WithdrawCmd.h"

WithdrawCmd::WithdrawCmd(std::shared_ptr<WithdrawTransaction> transaction)
{
    _transaction = transaction;
}
void execute()
{
    return;
}