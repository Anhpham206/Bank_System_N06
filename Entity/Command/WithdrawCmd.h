#ifndef _WITHDRAW_CMD_H_
#define _WITHDRAW_CMD_H_

#include "ICommand.h"

class WithdrawTransaction;

#include <memory>

class WithdrawCmd : public ICommand
{
private:
    std::shared_ptr<WithdrawTransaction> _transaction;

public:
    WithdrawCmd(std::shared_ptr<WithdrawTransaction> transaction);
    void execute() override;
    ~WithdrawCmd() override = default;
};

#endif