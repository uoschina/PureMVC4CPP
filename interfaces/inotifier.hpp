#ifndef __INOTIFIER_HPP__
#define __INOTIFIER_HPP__

#include <string>

class IMediator; 

typedef std::vector<IMediator*> ObserverMediators; 
typedef ObserverMediators::iterator ObserverMediatorsItr; 
class INotifier
{
public:
    virtual ~INotifier()
    {
    }

    /**
     * Send a <code>INotification</code>.
     * 
     * <P>
     * Convenience method to prevent having to construct new 
     * notification instances in our implementation code.</P>
     * 
     * @param notificationName the name of the notification to send
     * @param body the body of the notification (optional)
     * @param type the type of the notification (optional)
     */ 


	virtual void sendNotification(const INotification &  ) =0; 

	virtual void sendNotificationTo(const INotification& ,ObserverMediators&) =0; 


};



#endif // 
