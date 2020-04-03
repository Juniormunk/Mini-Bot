#pragma once

#include <Arduino.h>
#include <SerialTicker.h>

class SerialTicker;

struct SerialReadable
{
public:
    SerialReadable(SerialTicker *ticker)
    {
        this->ticker = ticker;
        //Add this object to get updates about serial events.
        //this->ticker->addTo(this);
        //getSerialTicker()->getName();
    };

    void println(String message);

    bool hasData();

    /**
     * Returns: The latest recieve string from the serial port.
     */
    String getLatestString();

    /**
     * Returns: The serialticker this object is using.
     */
    SerialTicker *getSerialTicker() { return ticker; };

    virtual void serialRecieveEvent(String line){};

private:
    SerialTicker *ticker;
    unsigned long lastReadTime = 0; // The time at which we accessed the last message from serial.
};