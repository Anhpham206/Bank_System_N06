#ifndef _TRANSFER_CMD_H_
#define _TRANSFER_CMD_H_

#include "ICommand.h"
#include "../Transaction/TransferTransaction.h"

#include <memory>

class TransferCmd : public ICommand
{
private:
    std::shared_ptr<TransferTransaction> _transaction;

public:
    TransferCmd(std::shared_ptr<TransferTransaction> transaction);
    void execute() override;
    ~TransferCmd() override = default;
};

#endif