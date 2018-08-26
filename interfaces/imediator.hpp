#ifndef __IMEDIATOR_HPP__
#define __IMEDIATOR_HPP__
#include <vector>
#include <string>

#include "inotification.hpp"

typedef std::vector<std::string> Interests; 
class IMediator;
typedef std::vector <IMediator*> InterestMediators; 

class IMediator 
{
    public:
        virtual ~IMediator(){}

        virtual std::string getName()  =0; 

        virtual  void * getViewComponent()  =0; 

        virtual void setViewComponent(void * pView)  =0;

		//get Interests list for special notification
		virtual InterestMediators getNotificationMediators(const INotification & notification)  
		{
			return InterestMediators(); 
		}
		
        virtual Interests listNotificationInterests() = 0; 

        virtual void handleNotification(const INotification&  notification) =0; 

        virtual void onRegister() = 0;
		
        virtual void onRemove()  = 0; 

private:
	std::string m_mediatorName; 
};


#endif // 



