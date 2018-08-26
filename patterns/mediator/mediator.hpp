#ifndef __MEDIATOR_HPP__
#define __MEDIATOR_HPP__
#include <vector>
#include <string>
#include "../interfaces/imediator.hpp"
#include "../patterns/observer/notifier.hpp"

class Mediator : public IMediator, public Notifier
{
    public:
        virtual ~Mediator(){}

        /**
         * The name of the <code>Mediator</code>. 
         * 
         * <P>
         * Typically, a <code>Mediator</code> will be written to serve
         * one specific control or group controls and so,
         * will not have a need to be dynamically named.</P>
         */
        //static const char * const NAME = "Mediator";

        /**
         * Constructor.
         */
		Mediator(const std::string & mediatorName="", void * viewComponent=NULL ) 
        {
            this->m_mediatorName = (mediatorName != "")?mediatorName:"Mediator"; 
            this->m_viewComponent = viewComponent;	
        }

        /**
         * Get the name of the <code>Mediator</code>.
         * @return the Mediator name
         */		
		virtual std::string getName()
        {	
            return m_mediatorName;
        }

        /**
         * Set the <code>IMediator</code>'s view component.
         * 
         * @param Object the view component
         */
        void setViewComponent( void * viewComponent )
        {
            this->m_viewComponent = viewComponent;
        }

        /**
         * Get the <code>Mediator</code>'s view component.
         * 
         * <P>
         * Additionally, an implicit getter will usually
         * be defined in the subclass that casts the view 
         * object to a type, like this:</P>
         * 
         * <listing>
         *		private get comboBox : mx.controls.ComboBox 
         *		{
         *			return viewComponent as mx.controls.ComboBox;
         *		}
         * </listing>
         * 
         * @return the view component
         */		
        void *  getViewComponent()
        {	
            return m_viewComponent;
        }

        /**
         * List the <code>INotification</code> names this
         * <code>Mediator</code> is interested in being notified of.
         * 
         * @return Array the list of <code>INotification</code> names 
         */
        Interests listNotificationInterests()
        {
            return Interests();
        }

        /**
         * Handle <code>INotification</code>s.
         * 
         * <P>
         * Typically this will be handled in a switch statement,
         * with one 'case' entry per <code>INotification</code>
         * the <code>Mediator</code> is interested in.
         */ 
        virtual void handleNotification( const INotification & notification) {}

        /**
         * Called by the View when the Mediator is registered
         */ 
        virtual void onRegister( ) {}

        /**
         * Called by the View when the Mediator is removed
         */ 
        virtual void onRemove( ) {}

        // the mediator name
    protected:

        std::string m_mediatorName;

        // The view component
        void * m_viewComponent;

};


#endif // 


