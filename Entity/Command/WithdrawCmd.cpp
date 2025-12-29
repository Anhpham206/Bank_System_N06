#include "WithdrawCmd.h"
#include "../Transaction/WithdrawTransaction.h"

WithdrawCmd::WithdrawCmd(std::shared_ptr<WithdrawTransaction> transaction)
{
    _transaction = transaction;
}
void WithdrawCmd::execute()
{
    _transaction->execute();
    return;
}