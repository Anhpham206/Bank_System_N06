#ifndef _DEPOSIT_CMD_H_
#define _DEPOSIT_CMD_H_

#include "ICommand.h"

#include <memory>

class DepositTransaction;

class DepositCmd : public ICommand
{
private:
    std::shared_ptr<DepositTransaction> _transaction;

public:
    DepositCmd(std::shared_ptr<DepositTransaction> transaction);
    bool execute() override;
    ~DepositCmd() override = default;
};

#endif