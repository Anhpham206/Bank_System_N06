#ifndef _TRANSFER_TRANSACTIONPARSER_H_
#define _TRANSFER_TRANSACTIONPARSER_H_

#include "../IParsable.h"
class TransferTransactionParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif