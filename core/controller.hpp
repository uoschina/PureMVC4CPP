#ifndef __CONTROLLER_HPP__
#define __CONTROLLER_HPP__
#include "../interfaces/icontroller.hpp"
#include "../utils/singlton.hpp"
#include <boost/bind.hpp>
using namespace boost; 


/**
 * A Singleton <code>IController</code> implementation.
 * 
 * <P>
 * In PureMVC, the <code>Controller</code> class follows the
 * 'Command and Controller' strategy, and assumes these 
 * responsibilities:
 * <UL>
 * <LI> Remembering which <code>ICommand</code>s 
 * are intended to handle which <code>INotifications</code>.</LI>
 * <LI> Registering itself as an <code>IObserver</code> with
 * the <code>View</code> for each <code>INotification</code> 
 * that it has an <code>ICommand</code> mapping for.</LI>
 * <LI> Creating a new instance of the proper <code>ICommand</code>
 * to handle a given <code>INotification</code> when notified by the <code>View</code>.</LI>
 * <LI> Calling the <code>ICommand</code>'s <code>execute</code>
 * method, passing in the <code>INotification</code>.</LI> 
 * </UL>
 * 
 * <P>
 * Your application must register <code>ICommands</code> with the 
 * Controller.
 * <P>
 * The simplest way is to subclass </code>Facade</code>, 
 * and use its <code>initializeController</code> method to add your 
 * registrations. 
 * */

#include "../interfaces/icommand.hpp"
#include "../utils/hash_map.hpp"
#include "../core/view.hpp"

using namespace HASH_MAP_NAMESPACE;

class Controller  : public IController, public Singlton<Controller>
{

    public:
        Controller( )
        {
            //if (m_instance != NULL) 
            //    throw "Singlton error";

            //m_instance = this;
            initializeController();	
        }

        void initializeController()
        {
            m_view = View::getInstance();
        }

    public:
        typedef hash_map<std::string,ICommand * >  CommandMap; 
        typedef CommandMap::iterator CommandMapItr; 
        /**
         * <code>Controller</code> Singleton Factory method.
         * 
         * @return the Singleton instance of <code>Controller</code>
         */

		/*
        static IController * getInstance() 
        {
            if ( m_instance == NULL ) 
            {
                m_instance = new Controller( );
            }
            return m_instance;
        }
		*/

        /**
         * If an <code>ICommand</code> has previously been registered 
         * to handle a the given <code>INotification</code>, then it is executed.
         * 
         * @param note an <code>INotification</code>
         */
        virtual void executeCommand(const  INotification & note ) 
        {
            CommandMapItr itr =  m_commandMap.find(note.getName()); 
            if (itr != m_commandMap.end())
            {
                ICommand * pCmd = itr->second; 
                if (pCmd != NULL)
                {
                    pCmd->execute(note); 
                }
            }
        }

        /**
         * Register a particular <code>ICommand</code> class as the handler 
         * for a particular <code>INotification</code>.
         * 
         * <P>
         * If an <code>ICommand</code> has already been registered to 
         * handle <code>INotification</code>s with this name, it is no longer
         * used, the new <code>ICommand</code> is used instead.</P>
         * 
         * The Observer for the new ICommand is only created if this the 
         * first time an ICommand has been regisered for this Notification name.
         * 
         * @param notificationName the name of the <code>INotification</code>
         * @param commandClassRef the <code>Class</code> of the <code>ICommand</code>
         */
        virtual void registerCommand( const std::string & notificationName ,ICommand * pCmd) 
        {
            CommandMapItr itr = m_commandMap.find(notificationName); 
            if (itr == m_commandMap.end())
            {
				NotifyMethod notifyMethod = boost::bind(&Controller::executeCommand,this,_1); 
				NotifyContext notifyContext(this); 
                m_view->registerObserver( notificationName, new Observer( notifyMethod, notifyContext) );
            }
            m_commandMap[ notificationName ] = pCmd;
        }


        /**
		 * Check if a Command is registered for a given Notification 
		 * 
		 * @param notificationName
		 * @return whether a Command is currently registered for the given <code>notificationName</code>.
		 */
		virtual bool hasCommand(const std::string &  notificationName ) 
		{
            return m_commandMap.find(notificationName) != m_commandMap.end(); 
		}


        /**
		 * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping.
		 * 
		 * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
		 */
		virtual void removeCommand( const std::string & notificationName  ) 
		{
			// if the Command is registered...
			if ( hasCommand( notificationName ) )
			{
				// remove the observer
				NotifyContext notifyContext; 
				m_view->removeObserver( notificationName, notifyContext);
							
				// remove the command
                m_commandMap.erase(notificationName); 
			}
		}


        // Local reference to View 
    protected:
        IView * m_view  ;
		
		// Mapping of Notification names to Command Class references
        hash_map<std::string,ICommand * >  m_commandMap; 

		// Singleton instance
		//static IController * m_instance ;

		// Message Constants
//		static const std::string SINGLETON_MSG = "Controller Singleton already constructed!";
};



#endif 


