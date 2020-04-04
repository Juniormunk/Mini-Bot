#ifndef MotorController_h
#define MotorController_h

#include <Arduino.h>
#include <Loopable.h>

class MotorController : Loopable
{
public:
    MotorController(String name) : Loopable(name){};
    //Instance methods

    void setOutput(float output) { this->output = output; };

    //Loopable methods
    void init();
    void periodic();
    void isfinsished(){};
    void end();

private:
    float output;
};

#endif