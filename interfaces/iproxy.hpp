#ifndef __IPROXY_HPP__
#define __IPROXY_HPP__

class IProxy
{

    public:
        virtual ~IProxy()
        {
        }
        /**
         * Get the Proxy name
         * 
         * @return the Proxy instance name
         */
        virtual std::string getName() const =0;

        /**
         * Set the data object
         * 
         * @param data the data object
         */
        virtual void setData( void *data) =0;

        /**
         * Get the data object
         * 
         * @return the data as type Object
         */
        virtual void * getData() =0; 

        /**
         * Called by the Model when the Proxy is registered
         */ 
        virtual void onRegister( ) =0;

        /**
         * Called by the Model when the Proxy is removed
         */ 
        virtual void onRemove( ) =0;
};

#endif // 

