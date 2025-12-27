#ifndef _BANKSYSTEMPARSER_H_
#define _BANKSYSTEMPARSER_H_

#include "../IParsable.h"
class BankSystemParser : public IParsable {
public:
    Object* parse(string data) override;
};

#endif