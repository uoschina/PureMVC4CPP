#ifndef __IFACADE_HPP__
#define __IFACADE_HPP__
#include <string> 

#include "inotifier.hpp"
#include "imediator.hpp"
#include "inotification.hpp"
#include "iproxy.hpp"
#include "icommand.hpp"

class IFacade : public  INotifier
{
    public:
        virtual ~IFacade(){}

        virtual void registerProxy(IProxy * proxy)  =0 ;

        virtual IProxy * retrieveProxy(const std::string & proxyName) =0; 

        virtual IProxy * removeProxy(const std::string & proxyName) =0; 

        virtual bool hasProxy (const std::string & proxyName) =0; 

        virtual void registerCommand(const std::string & noteName, ICommand *) =0; 

        virtual void removeCommand(const std::string & notificationName) =0;  

        virtual bool hasCommand(const std::string & notificationName) = 0; 

        virtual void registerMediator( IMediator * mediator) =0; 

        virtual IMediator *retrieveMediator(const std::string & mediatorName) =0; 

        virtual IMediator *removeMediator(const std::string & mediatorName) =0; 

        virtual bool hasMediator(const std::string & mediatorName) =0; 

        /**
		 * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
		 * 
		 * <P>
		 * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
		 * list are notified and are passed a reference to the <code>INotification</code> in 
		 * the order in which they were registered.</P>
		 * <P>
		 * NOTE: Use this method only if you are sending custom Notifications. Otherwise
		 * use the sendNotification method which does not require you to create the
		 * Notification instance.</P> 
		 * 
		 * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
		 */

        virtual void notifyObservers(const INotification & note) =0; 

};


#endif // 


