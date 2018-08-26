#ifndef __FACADE_HPP__
#define __FACADE_HPP__


/**
 * A base Singleton <code>IFacade</code> implementation.
 * 
 * <P>
 * In PureMVC, the <code>Facade</code> class assumes these 
 * responsibilities:
 * <UL>
 * <LI>Initializing the <code>Model</code>, <code>View</code>
 * and <code>Controller</code> Singletons.</LI> 
 * <LI>Providing all the methods defined by the <code>IModel, 
 * IView, & IController</code> interfaces.</LI>
 * <LI>Providing the ability to override the specific <code>Model</code>,
 * <code>View</code> and <code>Controller</code> Singletons created.</LI> 
 * <LI>Providing a single point of contact to the application for 
 * registering <code>Commands</code> and notifying <code>Observers</code></LI>
 * </UL>
 * <P>
 * Example usage:
 * <listing>
 *	import org.puremvc.as3.patterns.facade.&lowast;;
 * 
 *	import com.me.myapp.model.~~;
 *	import com.me.myapp.view.~~;
 *	import com.me.myapp.controller.~~;
 * 
 *	public class MyFacade extends Facade
 *	{
 *		// Notification constants. The Facade is the ideal
 *		// location for these constants, since any part
 *		// of the application participating in PureMVC 
 *		// Observer Notification will know the Facade.
 *		public static const GO_COMMAND:String = "go";
 * 		
 *		// Override Singleton Factory method 
 *		public static function getInstance() : MyFacade {
 *			if (instance == NULL) instance = new MyFacade();
 *			return instance as MyFacade;
 *		}
 * 		
 *		// optional initialization hook for Facade
 *		override public function initializeFacade() : void {
 *			super.initializeFacade();
 *			// do any special subclass initialization here
 *		}
 *	
 *		// optional initialization hook for Controller
 *		override public function initializeController() : void {
 *			// call super to use the PureMVC Controller Singleton. 
 *			super.initializeController();
 * 
 *			// Otherwise, if you're implmenting your own
 *			// IController, then instead do:
 *			// if ( controller != NULL ) return;
 *			// controller = MyAppController.getInstance();
 * 		
 *			// do any special subclass initialization here
 *			// such as registering Commands
 *			registerCommand( GO_COMMAND, com.me.myapp.controller.GoCommand )
 *		}
 *	
 *		// optional initialization hook for Model
 *		override public function initializeModel() : void {
 *			// call super to use the PureMVC Model Singleton. 
 *			super.initializeModel();
 * 
 *			// Otherwise, if you're implmenting your own
 *			// IModel, then instead do:
 *			// if ( model != NULL ) return;
 *			// model = MyAppModel.getInstance();
 * 		
 *			// do any special subclass initialization here
*			// such as creating and registering Model proxys
*			// that don't require a facade reference at
*			// construction time, such as fixed type lists
*			// that never need to send Notifications.
*			regsiterProxy( new USStateNamesProxy() );
* 			
*			// CAREFUL: Can't reference Facade instance in constructor 
*			// of new Proxys from here, since this step is part of
*			// Facade construction!  Usually, Proxys needing to send 
*			// notifications are registered elsewhere in the app 
*			// for this reason.
*		}
*	
*		// optional initialization hook for View
*		override public function initializeView() : void {
*			// call super to use the PureMVC View Singleton. 
*			super.initializeView();
* 
*			// Otherwise, if you're implmenting your own
*			// IView, then instead do:
*			// if ( view != NULL ) return;
*			// view = MyAppView.getInstance();
* 		
*			// do any special subclass initialization here
*			// such as creating and registering Mediators
*			// that do not need a Facade reference at construction
*			// time.
*			registerMediator( new LoginMediator() ); 
* 
*			// CAREFUL: Can't reference Facade instance in constructor 
*			// of new Mediators from here, since this is a step
*			// in Facade construction! Usually, all Mediators need 
*			// receive notifications, and are registered elsewhere in 
*			// the app for this reason.
*		}
*	}
* </listing>
* 
* @see org.puremvc.as3.core.model.Model Model
* @see org.puremvc.as3.core.view.View View
* @see org.puremvc.as3.core.controller.Controller Controller
* @see org.puremvc.as3.patterns.observer.Notification Notification
* @see org.puremvc.as3.patterns.mediator.Mediator Mediator
* @see org.puremvc.as3.patterns.proxy.Proxy Proxy
* @see org.puremvc.as3.patterns.command.SimpleCommand SimpleCommand
* @see org.puremvc.as3.patterns.command.MacroCommand MacroCommand
*/

#include "./core/controller.hpp"
#include "./core/model.hpp"
#include "./patterns/observer/notification.hpp"
#include "./interfaces/ifacade.hpp"
#include "./utils/singlton.hpp"
#include "../patterns/observer/facade_holder.hpp"

template<class T>
class Facade : public IFacade, public Singlton<T >
{
    public:
        /**
         * Constructor. 
         * 
         * <P>
         * This <code>IFacade</code> implementation is a Singleton, 
         * so you should not call the constructor 
         * directly, but instead call the static Singleton 
         * Factory method <code>Facade.getInstance()</code>
         * 
         * @throws Error Error if Singleton instance has already been constructed
         * 
         */
        Facade( ) 
		{
			m_controller = NULL; 
            //if (m_instance != NULL) throw "Singleton error";
			FacadeHolder::setFacade(this); 
            initializeFacade();	
        }

        /**
         * Initialize the Singleton <code>Facade</code> instance.
         * 
         * <P>
         * Called automatically by the constructor. Override in your
         * subclass to do any subclass specific initializations. Be
         * sure to call <code>super.initializeFacade()</code>, though.</P>
         */
        void initializeFacade() 
        {
            initializeModel();
            initializeController();
            initializeView();
        }

        /**
         * Facade Singleton Factory method
         * 
         * @return the Singleton instance of the Facade
         */
        //static IFacade * getInstance()
		//{
        //    if (m_instance == NULL) m_instance = new Facade( );
        //    return m_instance;
       // }

        /**
         * Initialize the <code>Controller</code>.
         * 
         * <P>
         * Called by the <code>initializeFacade</code> method.
         * Override this method in your subclass of <code>Facade</code> 
         * if one or both of the following are true:
         * <UL>
         * <LI> You wish to initialize a different <code>IController</code>.</LI>
         * <LI> You have <code>Commands</code> to register with the <code>Controller</code> at startup.</code>. </LI>		  
         * </UL>
         * If you don't want to initialize a different <code>IController</code>, 
         * call <code>super.initializeController()</code> at the beginning of your
         * method, then register <code>Command</code>s.
         * </P>
         */
        void initializeController( ) 
		{
            if ( m_controller != NULL ) 
				return;
			m_controller = Controller::getInstance();
        }

        /**
         * Initialize the <code>Model</code>.
         * 
         * <P>
         * Called by the <code>initializeFacade</code> method.
         * Override this method in your subclass of <code>Facade</code> 
         * if one or both of the following are true:
         * <UL>
         * <LI> You wish to initialize a different <code>IModel</code>.</LI>
         * <LI> You have <code>Proxy</code>s to register with the Model that do not 
         * retrieve a reference to the Facade at construction time.</code></LI> 
         * </UL>
         * If you don't want to initialize a different <code>IModel</code>, 
         * call <code>super.initializeModel()</code> at the beginning of your
         * method, then register <code>Proxy</code>s.
         * <P>
         * Note: This method is <i>rarely</i> overridden; in practice you are more
         * likely to use a <code>Command</code> to create and register <code>Proxy</code>s
         * with the <code>Model</code>, since <code>Proxy</code>s with mutable data will likely
         * need to send <code>INotification</code>s and thus will likely want to fetch a reference to 
         * the <code>Facade</code> during their construction. 
         * </P>
         */
        void initializeModel( )
		{
            //if ( m_model != NULL ) return;
			m_model = Model::getInstance();
        }


        /**
         * Initialize the <code>View</code>.
         * 
         * <P>
         * Called by the <code>initializeFacade</code> method.
         * Override this method in your subclass of <code>Facade</code> 
         * if one or both of the following are true:
         * <UL>
         * <LI> You wish to initialize a different <code>IView</code>.</LI>
         * <LI> You have <code>Observers</code> to register with the <code>View</code></LI>
         * </UL>
         * If you don't want to initialize a different <code>IView</code>, 
         * call <code>super.initializeView()</code> at the beginning of your
         * method, then register <code>IMediator</code> instances.
         * <P>
         * Note: This method is <i>rarely</i> overridden; in practice you are more
         * likely to use a <code>Command</code> to create and register <code>Mediator</code>s
         * with the <code>View</code>, since <code>IMediator</code> instances will need to send 
         * <code>INotification</code>s and thus will likely want to fetch a reference 
         * to the <code>Facade</code> during their construction. 
         * </P>
         */
        void initializeView( )
        {
            //if ( m_view != NULL ) return;
			m_view = View::getInstance();
        }

        /**
         * Register an <code>ICommand</code> with the <code>Controller</code> by Notification name.
         * 
         * @param notificationName the name of the <code>INotification</code> to associate the <code>ICommand</code> with
         * @param commandClassRef a reference to the Class of the <code>ICommand</code>
         */
		void registerCommand( const std::string & notificationName, ICommand * command) 
        {
            m_controller->registerCommand( notificationName, command );
        }

        /**
         * Remove a previously registered <code>ICommand</code> to <code>INotification</code> mapping from the Controller.
         * 
         * @param notificationName the name of the <code>INotification</code> to remove the <code>ICommand</code> mapping for
         */
		void removeCommand( const std::string & notificationName) 
        {
            m_controller->removeCommand( notificationName );
        }

        /**
         * Check if a Command is registered for a given Notification 
         * 
         * @param notificationName
         * @return whether a Command is currently registered for the given <code>notificationName</code>.
         */
		bool hasCommand( const std::string & notificationName) 
        {
            return m_controller->hasCommand(notificationName);
        }

        /**
         * Register an <code>IProxy</code> with the <code>Model</code> by name.
         * 
         * @param proxyName the name of the <code>IProxy</code>.
         * @param proxy the <code>IProxy</code> instance to be registered with the <code>Model</code>.
         */
        void registerProxy ( IProxy * proxy)	
        {
            m_model->registerProxy ( proxy );	
        }

        /**
         * Retrieve an <code>IProxy</code> from the <code>Model</code> by name.
         * 
         * @param proxyName the name of the proxy to be retrieved.
         * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
         */
		IProxy * retrieveProxy ( const std::string & proxyName)
        {
            return m_model->retrieveProxy ( proxyName );	
        }

        /**
         * Remove an <code>IProxy</code> from the <code>Model</code> by name.
         *
         * @param proxyName the <code>IProxy</code> to remove from the <code>Model</code>.
         * @return the <code>IProxy</code> that was removed from the <code>Model</code>
         */
		IProxy * removeProxy ( const std::string & proxyName)
        {
			IProxy * proxy  = NULL;
            if ( m_model != NULL ) 
				proxy = m_model->removeProxy ( proxyName );	
            return proxy;
        }

        /**
         * Check if a Proxy is registered
         * 
         * @param proxyName
         * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
         */
		bool hasProxy( const std::string & proxyName) 
        {
            return m_model->hasProxy( proxyName );
        }

        /**
         * Register a <code>IMediator</code> with the <code>View</code>.
         * 
         * @param mediatorName the name to associate with this <code>IMediator</code>
         * @param mediator a reference to the <code>IMediator</code>
         */
        void registerMediator( IMediator * mediator) 
        {
            if ( m_view != NULL ) 
				m_view->registerMediator( mediator );
        }

        /**
         * Retrieve an <code>IMediator</code> from the <code>View</code>.
         * 
         * @param mediatorName
         * @return the <code>IMediator</code> previously registered with the given <code>mediatorName</code>.
         */
		IMediator * retrieveMediator( const std::string & mediatorName)
        {
            return m_view->retrieveMediator( mediatorName ) ;
        }

        /**
         * Remove an <code>IMediator</code> from the <code>View</code>.
         * 
         * @param mediatorName name of the <code>IMediator</code> to be removed.
         * @return the <code>IMediator</code> that was removed from the <code>View</code>
         */
		IMediator * removeMediator( const std::string & mediatorName) 
        {
            IMediator  * mediator = NULL;
            if ( m_view != NULL ) 
				mediator = m_view->removeMediator( mediatorName );			
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
            return m_view->hasMediator( mediatorName );
        }

        /**
         * Create and send an <code>INotification</code>.
         * 
         * <P>
         * Keeps us from having to construct new notification 
         * instances in our implementation code.
         * @param notificationName the name of the notiification to send
         * @param body the body of the notification (optional)
         * @param type the type of the notification (optional)
         */ 
		virtual void sendNotification(const INotification & noti ) 
        {
            notifyObservers( noti );
        }

		virtual void sendNotification(const std::string & name)
		{
			Notification noti(name); 
			notifyObservers(noti); 
		}
		virtual void sendNotificationTo(const std::string & name ,ObserverMediators & observers) 
		{
			Notification noti(name); 
			notifyObservers(noti,observers);
		}

		virtual void sendNotificationTo(const INotification& noti,ObserverMediators & observers) 
		{
			notifyObservers(noti,observers);
		}

        /**
         * Notify <code>Observer</code>s.
         * <P>
         * This method is left public mostly for backward 
         * compatibility, and to allow you to send custom 
         * notification classes using the facade.</P>
         *<P> 
         * Usually you should just call sendNotification
         * and pass the parameters, never having to 
         * construct the notification yourself.</P>
         * 
         * @param notification the <code>INotification</code> to have the <code>View</code> notify <code>Observers</code> of.
         */
        void notifyObservers ( const INotification & notification) 
        {
            if ( m_view != NULL ) 
			{
                m_view->notifyObservers( notification );
			}
        }

		
		void notifyObservers(const INotification & noti, ObserverMediators & obers)
		{
			if (m_view != NULL)
			{
				m_view->notifyObservers(noti,obers);
			}
		}

    protected:
        // Private references to Model, View and Controller
        IController * m_controller ;
        IModel *m_model;
        IView *m_view;

        // The Singleton Facade instance.
        //static IFacade * m_instance ; 

        // Message Constants
        //const SINGLETON_MSG	: String = "Facade Singleton already constructed!";

};


#endif // 
