#ifndef Loopable_h
#define Loopable_h

#include <Arduino.h>

struct Loopable
{
public:
    Loopable(){};
    virtual void init()
    {
        hasInit = true;
    };
    /**
     * This will run every loop the arduino makes.
     */
    virtual void periodic(){};
    /**
     * This will run if the isFinished returns true;
     */
    virtual void end(){};
    /**
     * return if the loopable has finished what it is doing.
     */
    virtual bool isFinished() { return false; };
    /**
     * Returns: If the init method has been ran.
     */
    virtual bool getHasInit() { return hasInit; };

    /**
     * Returns: the name of the loopable object.
     */
    String getName() { return name; };

protected:
    //Stores if the init method has been ran.
    bool hasInit = false;

    //Stores the name of this loopable object.
    String name;
};

#endif