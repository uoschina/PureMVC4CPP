#ifndef __NOTIFICATION_HPP__
#define __NOTIFICATION_HPP__
#include "../../interfaces/inotification.hpp"

#include <string> 


class Notification : public INotification
{

    public:

        /**
         * Constructor. 
         * 
         * @param name name of the <code>Notification</code> instance. (required)
         * @param body the <code>Notification</code> body. (optional)
         * @param type the type of the <code>Notification</code> (optional)
         */
		Notification(const char * name)
		{
			this->m_name = name; 
		}

		Notification(const std::string & name)
		{
			this->m_name = name; 
		}

        Notification( const std::string & name, void* body, const std::string & type="")
        {
            this->m_name = name;
            this->m_type = type;
            this->m_body = body;
        }

        /**
         * Get the name of the <code>Notification</code> instance.
         * 
         * @return the name of the <code>Notification</code> instance.
         */
        std::string getName() const 
        {
            return m_name;
        }

        /**
         * Set the body of the <code>Notification</code> instance.
         */
        void setBody( void* body )
        {
            this->m_body = body;
        }

        /**
         * Get the body of the <code>Notification</code> instance.
         * 
         * @return the body object. 
         */
        void*  getBody() 
        {
            return m_body;
        }

        /**
         * Set the type of the <code>Notification</code> instance.
         */
        void setType( const std::string & type)
        {
            this->m_type = type;
        }

        /**
         * Get the type of the <code>Notification</code> instance.
         * 
         * @return the type  
         */
        std::string getType()
        {
            return m_type;
        }

        /**
         * Get the string representation of the <code>Notification</code> instance.
         * 
         * @return the string representation of the <code>Notification</code> instance.
         */
        std::string toString()
        {
            std::string msg= std::string("Notification Name: ")+getName();
            //msg += "\nBody:"+(( m_body == NULL )?"NULL":m_body.toString());
            msg += "\nType:"+(( m_type == "")?"":m_type);
            return msg;
        }
    private:
        // the name of the notification instance
        std::string m_name;
        // the type of the notification instance
        std::string m_type;
        // the body of the notification instance
        void*  m_body;
};


#endif // 

