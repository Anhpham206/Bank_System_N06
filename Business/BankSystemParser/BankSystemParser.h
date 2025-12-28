#ifndef _BANKSYSTEMPARSER_H_
#define _BANKSYSTEMPARSER_H_

#include "../IParsable.h"
class BankSystemParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif