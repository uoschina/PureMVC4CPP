#ifndef __PROXY_HPP__
#define __PROXY_HPP__
#include <string>

class Proxy : public Notifier , public IProxy
{

    public:
        //static const std::string NAME = "Proxy";

        /**
         * Constructor
         */
        Proxy( const std::string & proxyName, void * data = NULL ) 
        {
            this->m_proxyName = (!proxyName.empty())?proxyName:"Proxy"; 
            if (data != NULL) 
                setData(data);
        }

        /**
         * Get the proxy name
         */
        virtual std::string getName() const 
        {
            return m_proxyName;
        }		

        /**
         * Set the data object
         */
        virtual void setData(void *  data ) 
        {
            m_data = data;
        }

        /**
         * Get the data object
         */
        virtual void * getData() 
        {
            return m_data;
        }		

        /**
         * Called by the Model when the Proxy is registered
         */ 
        void onRegister( ) {}

        /**
         * Called by the Model when the Proxy is removed
         */ 
        void onRemove( ) {}


        // the proxy name
    protected:
        std::string m_proxyName;

        // the data object
        void *  m_data;
};


#endif // 

