// #ifndef Loopable_h
// #define Loopable_h

// #include <Arduino.h>

// class Loopable
// {
// public:
//     virtual void init() = 0;
//     virtual void periodic() = 0;
//     virtual void end() = 0;
//     virtual bool isFinished() = 0;
//     bool getHasInit() { return hasInit; };
//     String name;

// protected:
//     bool hasInit = false;
// };

// #endif

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