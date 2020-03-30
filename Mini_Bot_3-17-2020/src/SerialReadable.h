#ifndef SerialReadable_h
#define SerialReadable_h

#include <Arduino.h>
#include <SerialBuffer.h>

struct SerialReadable
{
public:
    SerialReadable(SerialBuffer *buffer) { this->buffer = buffer; };
    virtual void serialRecieveEvent(String line){};
    String readString()
    {
        // if (lastReadTime != buffer->getReadTime())
        // {
        //     lastReadTime = micros();
        //     return buffer->readString();
        // }
        // else
        // {
        return buffer->readString();

        //}
    };
    void println(String message)
    {
        buffer->println(message);
    }
    bool hasData()
    {
        if (lastReadTime != buffer->getReadTime())
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    String getLastString() { return buffer->readString(); }

    SerialBuffer *getSerialBuffer() { return buffer; };

private:
    SerialBuffer *buffer;
    unsigned long lastReadTime = 0; // The time at which we accessed the last message from serial.
};

#endif