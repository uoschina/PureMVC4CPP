#ifndef __INOTIFICATION_HPP__
#define __INOTIFICATION_HPP__
#include <string>


class INotification
{

public:
    virtual ~INotification()
    {
    }
    /**
     * Get the name of the <code>INotification</code> instance. 
     * No setter, should be set by constructor only
     */
    virtual std::string getName() const  =0;

    /**
     * Set the body of the <code>INotification</code> instance
     */
    virtual void setBody( void *  ) =0;

    /**
     * Get the body of the <code>INotification</code> instance
     */
    virtual void * getBody()=0;

    /**
     * Set the type of the <code>INotification</code> instance
     */
    virtual void setType( const std::string & type ) =0;

    /**
     * Get the type of the <code>INotification</code> instance
     */
    virtual std::string getType() =0;

    /**
     * Get the string representation of the <code>INotification</code> instance
     */
    virtual std::string toString() =0;
};



#endif // 


