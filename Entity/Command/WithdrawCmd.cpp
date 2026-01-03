#include "WithdrawCmd.h"
#include "../Transaction/WithdrawTransaction.h"

WithdrawCmd::WithdrawCmd(std::shared_ptr<WithdrawTransaction> transaction)
{
    _transaction = transaction;
}
bool WithdrawCmd::execute()
{
    return _transaction->execute();
}