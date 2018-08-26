#ifndef __OBSERVER_HPP__
#define __OBSERVER_HPP__

//#include "../patterns/observer/notifier.hpp"

class Observer : public IObserver
{

    /**
     * Constructor. 
     * 
     * <P>
     * The notification method on the interested object should take 
     * one parameter of type <code>INotification</code></P>
     * 
     * @param notifyMethod the notification method of the interested object
     * @param notifyContext the notification context of the interested object
     */
    public:
        virtual ~Observer(){}
		Observer( NotifyMethod& notifyMethod, NotifyContext & notifyContext) 
			:m_notifier(notifyMethod),m_context(notifyContext)
        {
            //setNotifyMethod( notifyMethod );
			//setNotifyContext(notifyContext);
        }

        /**
         * Set the notification method.
         * 
         * <P>
         * The notification method should take one parameter of type <code>INotification</code>.</P>
         * 
         * @param notifyMethod the notification (callback) method of the interested object.
         */
        void setNotifyMethod( NotifyMethod & notifyMethod)
        {
            m_notifier = notifyMethod;
        }

        /**
         * Set the notification context.
         * 
         * @param notifyContext the notification context (this) of the interested object.
         */
        void setNotifyContext(NotifyContext &  notifyContext )
        {
            m_context = notifyContext;
        }

        /**
         * Get the notification method.
         * 
         * @return the notification (callback) method of the interested object.
         */
        NotifyMethod getNotifyMethod()
        {
            return m_notifier;
        }

        /**
         * Get the notification context.
         * 
         * @return the notification context (<code>this</code>) of the interested object.
         */
        NotifyContext getNotifyContext()
        {
            return m_context;
        }

        /**
         * Notify the interested object.
         * 
         * @param notification the <code>INotification</code> to pass to the interested object's notification method.
         */
        void notifyObserver( const INotification &notification)
        {
			if (m_context)
			{
				if (m_notifier)
				{
					m_notifier(notification); 
				}
			}
			

            //this->getNotifyMethod().apply(this->getNotifyContext(),interests);
        }

        /**
         * Compare an object to the notification context. 
         * 
         * @param object the object to compare
         * @return boolean indicating if the object and the notification context are the same
         */
        bool compareNotifyContext( NotifyContext & context )
        {
            return context == this->m_context;
        }		

    private :
        NotifyMethod m_notifier;
        NotifyContext m_context;
};




#endif // 


