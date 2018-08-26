#ifndef __NOTIFYMETHOD_HPP__
#define __NOTIFYMETHOD_HPP__
#include <boost/function.hpp>

#include "notify_context.hpp"

/*
class NotifyMethod 
{
public:
	NotifyMethod(INotification * notification = NULL)
	{
		m_notification = notification; 
	}

	void apply(NotifyContext & context,Interests & interests)
	{

	}

private:
	INotification * m_notification;  
};
*/


typedef boost::function<void (const INotification & )> NotifyMethod; 


#endif // 



