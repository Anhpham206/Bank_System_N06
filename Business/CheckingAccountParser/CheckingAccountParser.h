#ifndef _CHECKINGACCOUNTPARSER_H_
#define _CHECKINGACCOUNTPARSER_H_

#include "../IParsable.h"
class CheckingAccountParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif