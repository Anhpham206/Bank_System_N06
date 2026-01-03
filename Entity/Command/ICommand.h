#ifndef _ICOMMAND_H_
#define _ICOMMAND_H_

class ICommand
{
public:
    virtual bool execute() = 0;

    virtual ~ICommand() = default;
};

#endif