#ifndef _DISPLAY_INFO_CMD_H_
#define _DISPLAY_INFO_CMD_H_

#include "ICommand.h"
#include "../Object.h"

#include <memory>

class DisplayInfoCmd : public ICommand
{
private:
    std::shared_ptr<Object> _object;

public:
    DisplayInfoCmd(std::shared_ptr<Object> object);
    void execute() override;
    ~DisplayInfoCmd() override = default;
};

#endif