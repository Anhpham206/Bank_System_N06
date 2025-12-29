#ifndef _DEPOSIT_TRANSACTIONPARSER_H_
#define _DEPOSIT_TRANSACTIONPARSER_H_

#include "../IParsable.h"
class DepositTransactionParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif