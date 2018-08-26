#ifndef __ICONTROLLER_HPP__
#define __ICONTROLLER_HPP__
#include <string>
#include "icommand.hpp"

class IController
{
    public:
        virtual ~IController(){}
        virtual void registerCommand(const std::string & notificationName, ICommand * ) =0; 

        virtual void executeCommand(const INotification & notification) =0; 
        
        virtual void removeCommand(const std::string & notificationName) =0; 

        virtual bool hasCommand(const std::string & notificationName) =0; 
};

#endif // 


