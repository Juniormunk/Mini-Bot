#ifndef PIDSensor_h
#define PIDSensor_h

#include <Arduino.h>

struct PIDSensor
{
public:
    PIDSensor(){};
    virtual float getValue(); //Returns the input for a pid controller
};

#endif