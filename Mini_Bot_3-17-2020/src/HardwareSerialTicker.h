#include <Arduino.h>
#include <Loopable.h>
#include <SerialReadable.h>
#include <SimpleList.h>
#include <SerialTicker.h>

class HardwareSerialTicker : public SerialTicker
{
public:
    HardwareSerialTicker(HardwareSerial serial, String name) : SerialTicker(name)
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

    //Loopable Methods
    void init(){};
    void periodic();
    void end(){};
    bool isFinished() { return false; };

private:
    HardwareSerial serial;
    SimpleList<SerialReadable *> *readables = new SimpleList<SerialReadable *>();
};
