#ifndef Watchdogable_h
#define Watchdogable_h

#include <Arduino.h>

struct Watchdogable
{
public:
    Watchdogable(unsigned long timeout) { this->timeout = timeout; };
    virtual bool getIsWatchdogTripped(); //Returns if the watchdog has been tripped (AKA: device is not responding.)
    virtual void updateWatchdog();       //Send an update message to the gyro to see if it is responding.
protected:
    unsigned long watchdogLastSend = 0;
    unsigned long watchdogLastRecieve = 0;
    unsigned long timeout = 600;
};

#endif