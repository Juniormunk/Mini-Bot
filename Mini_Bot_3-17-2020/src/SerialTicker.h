#pragma once
#include <Arduino.h>
#include <Loopable.h>
#include <SerialReadable.h>
#include <SimpleList.h>

struct SerialReadable;

class SerialTicker : public Loopable
{
public:
    SerialTicker(HardwareSerial serial, String name) : Loopable(name)
    {

        this->serial = serial;
        this->serial.begin(115200);
        this->serial.setTimeout(3);
    };

    //Instance Methods

    /**
     * Adds the object to get serial updates.
     */
    void addTo(SerialReadable *readable);

    /**
     * Removes the object from getting serial updates.
     * 
     * Returns: weather the object was found and removed from the list.
     */
    bool removeFrom(SerialReadable *readable);

    /**
     * Print to the serial port.
     */
    void println(String message);

    /**
     * Returns: the last information that was recieve over the serial port.
     */
    String readLatestString() { return latestString; };

    /**
     * Returns: the last time the serial port had new information.
     */
    unsigned long getReadTime() { return readTime; };

    //Loopable Methods
    void init(){};
    void periodic();
    void end(){};
    bool isFinished() { return false; };

private:
    HardwareSerial serial;
    String latestString = "";
    unsigned long readTime;
    SimpleList<SerialReadable *> *readables = new SimpleList<SerialReadable *>();
};
