#ifndef __ICOMMAND_HPP__
#define __ICOMMAND_HPP__
#include "inotification.hpp"

class ICommand
{
    public:
        virtual ~ICommand()
        {
        }
        virtual void execute(const INotification & notification) =0; 
};


#endif // 


