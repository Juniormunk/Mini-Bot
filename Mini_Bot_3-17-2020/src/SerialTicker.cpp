#include <SerialTicker.h>
#include <SerialReadable.h>

void SerialTicker::addTo(SerialReadable *readable)
{
    readables->add(readable);
};

bool SerialTicker::removeFrom(SerialReadable *readable)
{
    for (int i = 0; i < readables->size(); i++)
    {
        if (readables->get(i) == readable)
        {
            readables->remove(i);
            return true;
        }
    }
    return false;
};

void SerialTicker::println(String message)
{
    this->serial.println(message);
}
void SerialTicker::periodic()
{
    if (serial.available() > 0)
    {
        latestString = this->serial.readStringUntil('\n');
        readTime = micros();
        for (int i = 0; i < readables->size(); i++)
        {
            readables->get(i)->serialRecieveEvent(latestString);
        }
    }
};