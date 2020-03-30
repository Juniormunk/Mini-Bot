#ifndef SerialBuffer_h
#define SerialBuffer_h

#include <Arduino.h>
#include <PIDSensor.h>
#include <ErrorCode.h>
#include <Watchdogable.h>
#include <Loopable.h>

class SerialBuffer
{
public:
    SerialBuffer(HardwareSerial serial)
    {
        this->serial = serial;
        this->serial = serial;
        this->serial.begin(115200);
        this->serial.setTimeout(5);
    };
    String readString()
    {
        if (serial.available() > 0)
        {
            line = this->serial.readStringUntil('\n');
            readTime = micros();
        }
        return line;
    };
    void println(String message) { this->serial.println(message); };
    unsigned long getReadTime() { return readTime; };

private:
    HardwareSerial serial;
    unsigned long readTime = 0; //This is in micros
    String line = "";
};
#endif