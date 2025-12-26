#ifndef _CUSTOMERPARSER_H_
#define _CUSTOMERPARSER_H_

#include "../IParsable.h"
class CustomerParser : public IParsable {
public:
    Object* parse(string data) override;
};

#endif