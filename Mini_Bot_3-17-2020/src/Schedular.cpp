#include "Arduino.h"
#include "schedular.h"
#include "Loopable.h"

void Schedular::init()
{
    Serial.println("Schedular INIT");
    //Loopable::init();
    for (int i = 0; i < schedular->size(); i++)
    {
        Serial.print("Loop: ");
        Loopable *loopable = schedular->get(i);
        if (!loopable->getHasInit())
        {
            loopable->init();
        }
        Serial.println(loopable->getName());
    }
}
void Schedular::periodic()
{
    //Serial.println("Periodic");
    for (int i = 0; i < schedular->size(); i++)
    {
        Loopable *loopable = schedular->get(i);

        if (!loopable->getHasInit())
        {
            loopable->init();
        }

        if (loopable->isFinished())
        {
            loopable->end();
            schedular->remove(i);
            continue;
        }
        loopable->periodic();
    }
}

void Schedular::end()
{
    for (int i = 0; i < schedular->size(); i++)
    {
        Loopable *loopable = schedular->get(i);
        loopable->end();
        schedular->remove(i);
    }
}
bool Schedular::isFinished()
{
    return false;
}