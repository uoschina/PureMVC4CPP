#include "utils/hash_func.hpp"
#include "../interfaces/inotification.hpp"
#include "../interfaces/imediator.hpp"
#include "../interfaces/ifacade.hpp"
#include "../interfaces/icontroller.hpp"
#include "../core/view.hpp"
#include "../core/model.hpp"
#include "../core/controller.hpp"
#include "../patterns/facade/facade.hpp"
#include "../patterns/proxy/proxy.hpp"
#include "../patterns/command/simple_command.hpp"

//#include "../test/AppFacade.hpp"
#include <iostream>




class AppFacade : public Facade<AppFacade>
{
public:
	AppFacade():Facade<AppFacade>()
	{

	}
	void startup()
	{
		this->sendNotification("talk");
		this->sendNotification("walk");
		this->sendNotification("===");
	}

};

class MyCommand: public SimpleCommand
{
public:
	virtual void execute(const INotification & notification)
	{
		std::cout <<"Execute command " << notification.getName();
	}
};

class MyMediator : public Mediator
{
public:
	MyMediator():Mediator("test")
	{

	}

	 virtual Interests listNotificationInterests() 
	 {
		 Interests interests; 
		 interests.push_back("walk"); 
		 interests.push_back("talk"); 
		 interests.push_back("say"); 
		 return interests; 
	 }

	 virtual void handleNotification( const INotification&  notification) 
	 {
		 const std::string & noteName   = notification.getName(); 

		 if (noteName == "walk")
		 {
			 std::cout <<"process walk notification "<<std::endl; 
		 }else if (noteName == "talk")
		 {
			 std::cout <<"process talk notification "<<std::endl; 
		 }else if (noteName == "say")
		 {
			 std::cout <<"process say notification "<<std::endl; 
		 }
		 
	 }

};

class MyMediator2 : public Mediator
{
public:
	MyMediator2():Mediator("test2")
	{
		
	}

	virtual Interests listNotificationInterests() 
	{
		Interests interests; 
		interests.push_back("walk"); 
		//interests.push_back("talk"); 
		interests.push_back("say"); 
		return interests; 
	}

	virtual void handleNotification( const INotification&  notification) 
	{
		const std::string & noteName   = notification.getName(); 

		if (noteName == "walk")
		{
			std::cout <<"process walk notification "<<std::endl; 
		}else if (noteName == "talk")
		{
			std::cout <<"process talk notification "<<std::endl; 
		}else if (noteName == "say")
		{
			std::cout <<"process say notification "<<std::endl; 
		}

	}
};


class MyProxy : public Proxy 
{
    public:
        MyProxy():Proxy("MyProxy")
    {
    }

};


int main(int argc, char * argv[])
{

	View myview; 
	//IModel * mymodel = Model::getInstance();

	//IController * mycontroller = Controller::getInstance(); 

	MyCommand *pCmd = new MyCommand(); 

	AppFacade* facade = AppFacade::getInstance(); 
	MyMediator * mediator = new MyMediator(); 
	MyMediator2 * mediator2 = new MyMediator2(); 
	facade->registerMediator(mediator); 
	facade->registerMediator(mediator2); 
	facade->registerCommand("Startup",pCmd);

    facade->registerProxy(new MyProxy()); 


    IProxy * pPxy = facade->retrieveProxy("MyProxy");
    std::cout << "Proxy :"<< pPxy->getName() <<std::endl; 

	facade->sendNotification("Startup");
	ObserverMediators obers; 
	obers.push_back(mediator);
	facade->sendNotificationTo("walk",obers);

	facade->startup(); 

	return 0; 
}
