#ifndef _SAVINGACCOUNTPARSER_H_
#define _SAVINGACCOUNTPARSER_H_

#include "../IParsable.h"
class SavingAccountParser : public IParsable {
public:
    Object* parse(string data) override;
};

#endif