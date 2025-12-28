#ifndef _IPARSABLE_H_
#define _IPARSABLE_H_

#include "../Entity/Object.h"
#include <string>
#include <memory>
using std::shared_ptr, std::make_shared;
using std::string;

class IParsable
{
public:
    virtual shared_ptr<Object> parse(string data) = 0;
    virtual ~IParsable() = default;
};

#endif