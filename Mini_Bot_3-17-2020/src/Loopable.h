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
    virtual void periodic(){};
    virtual void end(){};
    virtual bool isFinished() { return false; };
    virtual bool getHasInit() { return hasInit; };
    String getName() { return name; };

protected:
    bool hasInit = false;
    String name;
};

#endif