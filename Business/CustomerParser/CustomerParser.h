#ifndef _CUSTOMERPARSER_H_
#define _CUSTOMERPARSER_H_

#include "../IParsable.h"
class CustomerParser : public IParsable
{
public:
    shared_ptr<Object> parse(string data) override;
};

#endif