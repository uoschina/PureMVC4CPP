#ifndef __VIEW_HPP__
#define __VIEW_HPP__
#include "../utils/hash_map.hpp"
#include <list>
#include <vector>
#include <boost/bind.hpp>
using namespace boost; 



/**
 * A Singleton <code>IView</code> implementation.
 * 
 * <P>
 * In PureMVC, the <code>View</code> class assumes these responsibilities:
 * <UL>
 * <LI>Maintain a cache of <code>IMediator</code> instances.</LI>
 * <LI>Provide methods for registering, retrieving, and removing <code>IMediators</code>.</LI>
 * <LI>Notifiying <code>IMediators</code> when they are registered or removed.</LI>
 * <LI>Managing the observer lists for each <code>INotification</code> in the application.</LI>
 * <LI>Providing a method for attaching <code>IObservers</code> to an <code>INotification</code>'s observer list.</LI>
 * <LI>Providing a method for broadcasting an <code>INotification</code>.</LI>
 * <LI>Notifying the <code>IObservers</code> of a given <code>INotification</code> when it broadcast.</LI>
 * </UL>
 * 
 * @see org.puremvc.as3.patterns.mediator.Mediator Mediator
 * @see org.puremvc.as3.patterns.observer.Observer Observer
 * @see org.puremvc.as3.patterns.observer.Notification Notification
 */

#include "../interfaces/iview.hpp"
#include "../patterns/observer/obversver.hpp"
#include "../patterns/mediator/mediator.hpp"
#include "../utils/singlton.hpp"

using namespace HASH_MAP_NAMESPACE;
class View : public IView, public Singlton<View>
{

    /**
     * Constructor. 
     * 
     * <P>
     * This <code>IView</code> implementation is a Singleton, 
     * so you should not call the constructor 
     * directly, but instead call the static Singleton 
     * Factory method <code>View.getInstance()</code>
     * 
     * @throws Error Error if Singleton instance has already been constructed
     * 
     */
    public:
		typedef hash_map<std::string, IMediator * > MediatorMap; 
		typedef MediatorMap::iterator MediatorMapItr; 

        typedef std::vector<IObserver*>  ObserverArray; 
        typedef ObserverArray::iterator ObserverArrayItr; 

        typedef hash_map<std::string, ObserverArray >  ObserverMap; 
        typedef ObserverMap::iterator ObserverMapItr; 

        View( )
        {
            //if (m_instance != NULL) throw "singleton error";
            //m_instance = this;
            initializeView();	
        }

        /**
         * Initialize the Singleton View instance.
         * 
         * <P>
         * Called automatically by the constructor, this
         * is your opportunity to initialize the Singleton
         * instance in your subclass without overriding the
         * constructor.</P>
         * 
         * @return void
         */
        void initializeView(  ) 
        {
        }

        /**
         * View Singleton Factory method.
         * 
         * @return the Singleton instance of <code>View</code>
         * /
        static  IView * getInstance() 
        {
            if ( m_instance == NULL ) 
                m_instance = new View( );
            return m_instance;
        }
		*/

        /**
         * Register an <code>IObserver</code> to be notified
         * of <code>INotifications</code> with a given name.
         * 
         * @param notificationName the name of the <code>INotifications</code> to notify this <code>IObserver</code> of
         * @param observer the <code>IObserver</code> to register
         */
        virtual void registerObserver ( const std::string & notificationName, IObserver * observer) 
        {

            ObserverMapItr itr = m_observerMap.find(notificationName); 
            if (itr != m_observerMap.end())
            {
                itr->second.push_back(observer); 
            }
            else  
            {
                ObserverArray observers; 
                observers.push_back(observer); 
                m_observerMap[notificationName] = observers; 
            }
        }

		/**
		* Remove the observer for a given notifyContext from an observer list for a given Notification name.
		* <P>
		* @param notificationName which observer list to remove from 
		* @param notifyContext remove the observer with this object as its notifyContext
		*/
		void removeObserver( const std::string & notificationName,NotifyContext &notifyContext)
		{
			// the observer list for the notification under inspection
			ObserverMapItr itr = m_observerMap.find(notificationName); 
			if (itr  != m_observerMap.end()) 
			{
				ObserverArray observers = itr->second;//cloned

				// find the observer for the notifyContext
				for ( ObserverArrayItr oitr = observers.begin(); oitr != observers.end(); ++oitr) 
				{

					//Observer observer(NotifyMethod(),notifyContext); 
					//if ( observer.compareNotifyContext( notifyContext ) == true ) 
					//{
					//	// there can only be one Observer for a given notifyContext 
					//	// in any given Observer list, so remove it and break
					//	observers.erase(oitr);
					//	break;
					//}

				}

				// Also, when a Notification's Observer list length falls to 
				// zero, delete the notification key from the observer map
				if ( observers.empty()) 
				{
					m_observerMap.erase(notificationName);
				}
			}
		} 

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
        virtual void notifyObservers( const INotification &notification) 
        {
            ObserverMapItr itr = m_observerMap.find(notification.getName()); 
            if (itr != m_observerMap.end())
            {

                // Copy observers from reference array to working array, 
                // since the reference array may change during the notification loop
                
                // Get a reference to the observers list for this notification name
                ObserverArray observers = itr->second;

                // Notify Observers from the working array				
                for (size_t i = 0; i < observers.size(); i++) 
                {
                    IObserver * pObserver = observers[i];
                    pObserver->notifyObserver( notification );
                }
            }
        }

		virtual void notifyObservers(const INotification & notification,ObserverMediators &obers)
		{
			for (ObserverMediatorsItr itr = obers.begin(); itr != obers.end(); ++itr)
			{
				(*itr)->handleNotification(notification);
			}
		}

      

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
        virtual void registerMediator( IMediator * mediator ) 
        {
            // do not allow re-registration (you must to removeMediator fist)
			if (m_mediatorMap.find(mediator->getName()) != m_mediatorMap.end())
				return; 

            // Register the Mediator for retrieval by name
            m_mediatorMap[ mediator->getName() ] = mediator;

            // Get Notification interests, if any.
			Interests interests= mediator->listNotificationInterests();

            // Register Mediator as an observer for each of its notification interests
            if ( !interests.empty()) 
            {
                // Create Observer referencing this mediator's handlNotification method
                //var observer:Observer = new Observer( mediator->handleNotification, mediator );
				NotifyMethod notifyMethod = boost::bind(&IMediator::handleNotification,mediator,_1);
				NotifyContext notifyContext(this); 
				Observer * observer  = new Observer(notifyMethod,notifyContext); 

                // Register Mediator as Observer for its list of Notification interests
                for ( size_t i =0;  i<interests.size(); i++ ) 
				{
                    registerObserver( interests[i],  observer );
                }			
            }

            // alert the mediator that it has been registered
            mediator->onRegister();
        }

        /**
         * Retrieve an <code>IMediator</code> from the <code>View</code>.
         * 
         * @param mediatorName the name of the <code>IMediator</code> instance to retrieve.
         * @return the <code>IMediator</code> instance previously registered with the given <code>mediatorName</code>.
         */
        virtual IMediator * retrieveMediator( const std::string & mediatorName) 
        {
			MediatorMapItr itr = m_mediatorMap.find(mediatorName); 
			if(itr != m_mediatorMap.end())
			{
				return itr->second; 
			}
			return NULL;
        }

        /**
         * Remove an <code>IMediator</code> from the <code>View</code>.
         * 
         * @param mediatorName name of the <code>IMediator</code> instance to be removed.
         * @return the <code>IMediator</code> that was removed from the <code>View</code>
         */
        virtual IMediator * removeMediator( const std::string & mediatorName) 
        {
            // Retrieve the named mediator
			MediatorMapItr itr = m_mediatorMap.find(mediatorName); 

			IMediator * mediator = NULL;
            if ( itr != m_mediatorMap.end()) 
            {
				mediator = itr->second; 
                // for every notification this mediator is interested in...
				Interests interests= mediator->listNotificationInterests();
                for ( size_t i =0; i<interests.size(); i++ ) 
                {
                    // remove the observer linking the mediator 
                    // to the notification interest					
					NotifyContext notifyContext(mediator); 
                    removeObserver( interests[i], notifyContext);
                }	

                // remove the mediator from the map		
				m_mediatorMap.erase(mediatorName);

                // alert the mediator that it has been removed
                mediator->onRemove();
            }
            return mediator;
        }

        /**
         * Check if a Mediator is registered or not
         * 
         * @param mediatorName
         * @return whether a Mediator is registered with the given <code>mediatorName</code>.
         */
        bool hasMediator( const std::string & mediatorName) 
        {
			return m_mediatorMap.find(mediatorName) != m_mediatorMap.end(); 
        }

        // Mapping of Mediator names to Mediator instances
    protected:
		MediatorMap m_mediatorMap ;

        // Mapping of Notification names to Observer lists
        ObserverMap m_observerMap	;

        // Singleton instance
        //static IView * m_instance;
        // Message Constants
        //const std::string SINGLETON_MSG = "View Singleton already constructed!";
};





#endif // 
