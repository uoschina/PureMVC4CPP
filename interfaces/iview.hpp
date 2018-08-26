#ifndef __IVIEW_HPP__
#define __IVIEW_HPP__

#include <string>
#include "iobserver.hpp"
#include "imediator.hpp"

class IView 
{

public:
    virtual ~IView(){}
    /**
     * Register an <code>IObserver</code> to be notified
     * of <code>INotifications</code> with a given name.
     * 
     * @param notificationName the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
     * @param observer the <code>IObserver</code> to register
     */
    virtual void registerObserver( const std::string & notificationName,IObserver *observer) =0;

    /**
     * Remove a group of observers from the observer list for a given Notification name.
     * <P>
     * @param notificationName which observer list to remove from 
     * @param notifyContext removed the observers with this object as their notifyContext
     */
    virtual void removeObserver( const std::string & notificationName,NotifyContext & notifyContext) =0;

    /**
     * Notify the <code>IObservers</code> for a particular <code>INotification</code>.
     * 
     * <P>
     * All previously attached <code>IObservers</code> for this <code>INotification</code>'s
     * list are notified and are passed a reference to the <code>INotification</code> in 
     * the order in which they were registered.</P>
     * 
     * @param notification the <code>INotification</code> to notify <code>IObservers</code> of.
     */
    virtual void notifyObservers( const INotification & note)  =0;

	virtual void notifyObservers(const INotification & notification,ObserverMediators &obers) =0;

    /**
     * Register an <code>IMediator</code> instance with the <code>View</code>.
     * 
     * <P>
     * Registers the <code>IMediator</code> so that it can be retrieved by name,
     * and further interrogates the <code>IMediator</code> for its 
     * <code>INotification</code> interests.</P>
     * <P>
     * If the <code>IMediator</code> returns any <code>INotification</code> 
     * names to be notified about, an <code>Observer</code> is created encapsulating 
     * the <code>IMediator</code> instance's <code>handleNotification</code> method 
     * and registering it as an <code>Observer</code> for all <code>INotifications</code> the 
     * <code>IMediator</code> is interested in.</p>
     * 
     * @param mediatorName the name to associate with this <code>IMediator</code> instance
     * @param mediator a reference to the <code>IMediator</code> instance
     */
    virtual void registerMediator( IMediator *mediator)  =0;

    /**
     * Retrieve an <code>IMediator</code> from the <code>View</code>.
     * 
     * @param mediatorName the name of the <code>IMediator</code> instance to retrieve.
     * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
     */
    virtual IMediator * retrieveMediator(const std::string &  mediatorName)  =0;

    /**
     * Remove an <code>IMediator</code> from the <code>View</code>.
     * 
     * @param mediatorName name of the <code>IMediator</code> instance to be removed.
     * @return the <code>IMediator</code> that was removed from the <code>View</code>
     */
    virtual IMediator * removeMediator( const std::string & mediatorName)  =0;

    /**
     * Check if a Mediator is registered or not
     * 
     * @param mediatorName
     * @return whether a Mediator is registered with the given <code>mediatorName</code>.
     */
    virtual bool hasMediator( const std::string & mediatorName)  =0;

};


#endif // 

