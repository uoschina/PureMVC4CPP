#ifndef __IMODEL_HPP__
#define __IMODEL_HPP__
#include <string>
#include "./iproxy.hpp"

class IModel 
{
public:
    virtual ~IModel(){}
    /**
     * Register an <code>IProxy</code> instance with the <code>Model</code>.
     * 
     * @param proxyName the name to associate with this <code>IProxy</code> instance.
     * @param proxy an object reference to be held by the <code>Model</code>.
     */
    virtual void registerProxy( IProxy * proxy ) =0;

    /**
     * Retrieve an <code>IProxy</code> instance from the Model.
     * 
     * @param proxyName
     * @return the <code>IProxy</code> instance previously registered with the given <code>proxyName</code>.
     */
    virtual IProxy * retrieveProxy( const std::string & proxyName)=0 ;

    /**
     * Remove an <code>IProxy</code> instance from the Model.
     * 
     * @param proxyName name of the <code>IProxy</code> instance to be removed.
     * @return the <code>IProxy</code> that was removed from the <code>Model</code>
     */
    virtual IProxy * removeProxy( const std::string & proxyName) =0;

    /**
     * Check if a Proxy is registered
     * 
     * @param proxyName
     * @return whether a Proxy is currently registered with the given <code>proxyName</code>.
     */
    virtual bool hasProxy(const std::string &  proxyName) =0;

};

#endif // 

