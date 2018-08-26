#ifndef __IOBSERVER_HPP__
#define __IOBSERVER_HPP__

#include "notify_method.hpp"
#include "inotification.hpp"


class IObserver
{
public:

    virtual ~IObserver(){}
	/**
	* Set the notification method.
	* 
	* <P>
	* The notification method should take one parameter of type <code>INotification</code></P>
	* 
	* @param notifyMethod the notification (callback) method of the interested object
	*/
	virtual void setNotifyMethod( NotifyMethod & notifyMethod)=0;

	/**
	* Set the notification context.
	* 
	* @param notifyContext the notification context (this) of the interested object
	*/
	virtual void setNotifyContext( NotifyContext & notifyContext)=0;

	/**
	* Notify the interested object.
	* 
	* @param notification the <code>INotification</code> to pass to the interested object's notification method
	*/
	virtual void notifyObserver( const INotification & notification)=0;

	/**
	* Compare the given object to the notificaiton context object.
	* 
	* @param object the object to compare.
	* @return boolean indicating if the notification context and the object are the same.
	*/
	virtual bool compareNotifyContext( NotifyContext & context)=0;
};



#endif //

