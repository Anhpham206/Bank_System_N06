#ifndef _WITHDRAW_TRANSACTIONPARSER_H_
#define _WITHDRAW_TRANSACTIONPARSER_H_

#include "../IParsable.h"
class WithdrawTransactionParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif