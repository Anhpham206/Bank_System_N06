#ifndef _IPARSABLE_H_
#define _IPARSABLE_H_

#include "../Entity/Object.h"
#include <string>
using std::string;

class IParsable {
public:
    virtual Object* parse(string data) = 0;
    virtual ~IParsable() = default;
};

#endif