#ifndef _SAVINGACCOUNTPARSER_H_
#define _SAVINGACCOUNTPARSER_H_

#include "../IParsable.h"
class SavingAccountParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif