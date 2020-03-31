#include <SerialReadable.h>
#include <SerialTicker.h>

void SerialReadable::println(String message)
{
    ticker->println(message);
}

bool SerialReadable::hasData()
{
    if (lastReadTime != ticker->getReadTime())
    {
        return true;
    }
    else
    {
        return false;
    }
}

String SerialReadable::getLatestString() { return ticker->readLatestString(); }