#ifndef __MODEL_HPP__
#define __MODEL_HPP__
#include "../utils/hash_map.hpp"
#include "../utils/singlton.hpp"


/**
 * A Singleton <code>IModel</code> implementation.
 * 
 * <P>
 * In PureMVC, the <code>Model</code> class provides
 * access to model objects (Proxies) by named lookup. 
 * 
 * <P>
 * The <code>Model</code> assumes these responsibilities:</P>
 * 
 * <UL>
 * <LI>Maintain a cache of <code>IProxy</code> instances.</LI>
 * <LI>Provide methods for registering, retrieving, and removing 
 * <code>IProxy</code> instances.</LI>
 * </UL>
 * 
 * <P>
 * Your application must register <code>IProxy</code> instances 
 * with the <code>Model</code>. Typically, you use an 
 * <code>ICommand</code> to create and register <code>IProxy</code> 
 * instances once the <code>Facade</code> has initialized the Core 
 * actors.</p>
 *
 * @see org.puremvc.as3.patterns.proxy.Proxy Proxy
 * @see org.puremvc.as3.interfaces.IProxy IProxy
 */
#include "../interfaces/imodel.hpp"

class Model : public IModel, public Singlton<Model>
{
    public:

        virtual ~Model(){}
        /**
         * Constructor. 
         * 
         * <P>
         * This <code>IModel</code> implementation is a Singleton, 
         * so you should not call the constructor 
         * directly, but instead call the static Singleton 
         * Factory method <code>Model.getInstance()</code>
         * 
         * @throws Error Error if Singleton instance has already been constructed
         * 
         */
        Model()
        {
            initializeModel();	
        }
    public:
        typedef hash_map<std::string,IProxy * > PROXY_MAP; 
        typedef PROXY_MAP::iterator  PROXY_MAP_ITR; 

        /**
         * Initialize the Singleton <code>Model</code> instance.
         * 
         * <P>
         * Called automatically by the constructor, this
         * is your opportunity to initialize the Singleton
         * instance in your subclass without overriding the
         * constructor.</P>
         * 
         * @return void
         */
    protected:
        void initializeModel() 
        {
        }

        /**
         * <code>Model</code> Singleton Factory method.
         * 
         * @return the Singleton instance
         */
    public:

        /**
         * Register an <code>IProxy</code> with the <code>Model</code>.
         * 
         * @param proxy an <code>IProxy</code> to be held by the <code>Model</code>.
         */
        void registerProxy( IProxy * proxy ) 
        {
            m_proxyMap[ proxy->getName() ] = proxy;
            proxy->onRegister();
        }

        /**
         * Retrieve an <code>IProxy</code> from the <code>Model</code>.
         * 
         * @param proxyName
         * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
         */
        IProxy *retrieveProxy( const std::string & proxyName)
        {
            PROXY_MAP_ITR itr = m_proxyMap.find(proxyName); 
            if (itr != m_proxyMap.end())
            {
                return itr->second; 
            }
            return NULL; 
        }

        /**
         * Check if a Proxy is registered
         * 
         * @param proxyName
         * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
         */
        bool hasProxy( const std::string & proxyName)  
        {
            return m_proxyMap.end() !=  m_proxyMap.find(proxyName); 
        }

        /**
         * Remove an <code>IProxy</code> from the <code>Model</code>.
         * 
         * @param proxyName name of the <code>IProxy</code> instance to be removed.
         * @return the <code>IProxy</code> that was removed from the <code>Model</code>
         */
        IProxy *removeProxy( const std::string & proxyName) 
        {

            PROXY_MAP_ITR itr = m_proxyMap.find(proxyName); 
            IProxy * proxy = NULL; 
            if (itr != m_proxyMap.end())
            {
                proxy = itr->second; 
                m_proxyMap.erase(itr); 
            }
            return proxy;
        }

        // Mapping of proxyNames to IProxy instances
    protected:
        PROXY_MAP m_proxyMap ;
        // Message Constants
};

#endif // 



