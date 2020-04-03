#include <SoftwareSerialTicker.h>
#include <SerialReadable.h>

void SoftwareSerialTicker::addTo(SerialReadable *readable)
{
    readables->add(readable);
}

bool SoftwareSerialTicker::removeFrom(SerialReadable *readable)
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
}

void SoftwareSerialTicker::println(String message)
{
    this->serial.println(message);
}
void SoftwareSerialTicker::periodic()
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
}