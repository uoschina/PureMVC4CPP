#ifndef __NOTIFIER_HPP__
#define __NOTIFIER_HPP__
#include <string>
#include "../../interfaces/inotifier.hpp"
class IFacade; 

class Notifier : public INotifier
{
    /**
     * Create and send an <code>INotification</code>.
     * 
     * <P>
     * Keeps us from having to construct new INotification 
     * instances in our implementation code.
     * @param notificationName the name of the notiification to send
     * @param body the body of the notification (optional)
     * @param type the type of the notification (optional)
     */ 
    public:
        virtual ~Notifier(){}
		virtual void sendNotification( const INotification & ) 
		{
		}
	
		virtual void sendNotificationTo(const INotification& ,ObserverMediators&) 
		{

		}

        // Local reference to the Facade Singleton
    protected:
        IFacade * m_facade ;

};


#endif //

