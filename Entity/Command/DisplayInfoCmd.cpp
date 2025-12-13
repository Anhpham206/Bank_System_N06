#include "DisplayInfoCmd.h"

#include <iostream>

DisplayInfoCmd::DisplayInfoCmd(std::shared_ptr<Object> object)
{
    _object = object;
}
void DisplayInfoCmd::execute()
{
    std::cout << _object->info();
}