#ifndef MotorController_h
#define MotorController_h

#include <Arduino.h>
#include <Loopable.h>

class MotorController : public Loopable
{
public:
    MotorController(String name, u_int8_t en_pin, u_int8_t pinA, u_int8_t pinB) : Loopable(name)
    {
        this->en_pin = en_pin;
        this->pinA = pinA;
        this->pinB = pinB;
        pinMode(en_pin, OUTPUT);
        pinMode(pinA, OUTPUT);
        pinMode(pinB, OUTPUT);
    };
    //Instance methods

    void setOutput(float output) { this->output = output; };
    void setBrakeMode(bool shouldBrake) { this->shouldBrake = shouldBrake; };
    void setReversed(bool shouldReverse) { this->shouldReverse = shouldReverse; };

    //Loopable methods
    void init() { analogWrite(en_pin, 0); };
    void periodic()
    {
        int value = abs(output) * 255;
        if (output > 0)
        {
            if (shouldReverse)
            {
                digitalWrite(pinB, HIGH);
                digitalWrite(pinA, LOW);
                analogWrite(en_pin, value);
            }
            else
            {
                Serial.println(pinA);
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, LOW);
                analogWrite(en_pin, value);
            }
        }

        if (output < 0)
        {
            if (shouldReverse)
            {
                digitalWrite(pinB, LOW);
                digitalWrite(pinA, HIGH);
                analogWrite(en_pin, value);
            }
            else
            {
                digitalWrite(pinA, LOW);
                digitalWrite(pinB, HIGH);
                analogWrite(en_pin, value);
            }
        }

        if (output == 0)
        {
            if (!shouldBrake)
                analogWrite(en_pin, 0);

            if (shouldBrake)
            {
                digitalWrite(pinA, HIGH);
                digitalWrite(pinB, HIGH);
                analogWrite(en_pin, 255);
            }
        }
    };
    bool isfinsished() { return false; };
    void end() { analogWrite(en_pin, 0); };

private:
    u_int8_t en_pin, pinA, pinB;
    float output = 0;
    bool shouldBrake = false;
    bool shouldReverse = false;
};

#endif