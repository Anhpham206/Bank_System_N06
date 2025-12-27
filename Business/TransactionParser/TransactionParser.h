#ifndef _TRANSACTIONPARSER_H_
#define _TRANSACTIONPARSER_H_

#include "../IParsable.h"
class TransactionParser : public IParsable {
public:
    Object* parse(string data) override;
};

#endif