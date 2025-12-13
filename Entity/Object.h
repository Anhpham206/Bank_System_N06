#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <string>

using std::string;

class Object
{
public:
    virtual string info() = 0;
};

#endif