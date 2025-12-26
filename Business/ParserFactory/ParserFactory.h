#ifndef _PARSERFACTORY_H_
#define _PARSERFACTORY_H_

#include "../IParsable.h"
#include <string>

class ParserFactory {
public:
    static IParsable* create(std::string type);
};

#endif