#ifndef __NOTIFY_CONTEXT_HPP__
#define __NOTIFY_CONTEXT_HPP__

class NotifyContext
{
public:
	NotifyContext(void * pCtx = NULL) { context = pCtx; }

	void * context;  //the owner of the notify method
	bool operator == (const NotifyContext & self)const 
	{
		return this->context == self.context; 
	}
	operator bool ()const 
	{
		return context != NULL; 
	}
	bool  operator  !()const 
	{
		return context == NULL; 
	}
};

/*
bool operator ==(NotifyContext & left, NotifyContext & right)
{
	return left.context == right.context; 
}
*/


#endif // 

 
