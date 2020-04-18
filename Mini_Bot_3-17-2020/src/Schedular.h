#ifndef Schedular_h
#define Schedular_h

#include <Arduino.h>
#include <Loopable.h>
#include <SimpleList.h>

class Schedular
{
public:
    Schedular(SimpleList<Loopable *> *schedular) { this->schedular = schedular; };
    void init();
    void periodic();
    void end();
    bool isFinished();

    Loopable *getLoopableByName(String name);
    //void add(Loopable loopable);
    //void remove(Loopable loopable);

private:
    SimpleList<Loopable *> *schedular;
};

#endif