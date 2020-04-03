#pragma once
#include <Arduino.h>
#include <Loopable.h>
#include <SerialReadable.h>
#include <SimpleList.h>
#include <SerialTicker.h>

struct SerialReadable;

struct SerialTicker : public Loopable
{
public:
    SerialTicker(String name) : Loopable(name){};

    //Instance Methods

    /**
     * Adds the object to get serial updates.
     */
    virtual void addTo(SerialReadable *readable) = 0;

    /**
     * Removes the object from getting serial updates.
     * 
     * Returns: weather the object was found and removed from the list.
     */
    virtual bool removeFrom(SerialReadable *readable) = 0;

    /**
     * Print to the serial port.
     */
    virtual void println(String message) = 0;

    /**
     * Returns: the last information that was recieve over the serial port.
     */
    String readLatestString() { return latestString; };

    /**
     * Returns: the last time the serial port had new information.
     */
    unsigned long getReadTime() { return readTime; };

    //Loopable Methods
    virtual void init() = 0;
    virtual void periodic() = 0;
    virtual void end() = 0;
    virtual bool isFinished() = 0;

protected:
    String latestString = "";
    unsigned long readTime;
};
