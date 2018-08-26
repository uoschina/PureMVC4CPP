#ifndef __SIMPLE_COMMAND_HPP__
#define __SIMPLE_COMMAND_HPP__

#include "../../interfaces/icommand.hpp"
#include "../../patterns/observer/notifier.hpp"

class SimpleCommand :public Notifier ,public ICommand
{
    public:

        /**
         * Fulfill the use-case initiated by the given <code>INotification</code>.
         * 
         * <P>
         * In the Command Pattern, an application use-case typically
         * begins with some user action, which results in an <code>INotification</code> being broadcast, which 
         * is handled by business logic in the <code>execute</code> method of an
         * <code>ICommand</code>.</P>
         * 
         * @param notification the <code>INotification</code> to handle.
         */
        virtual void execute( const INotification & notification) 
        {

        }
};

#endif // 
