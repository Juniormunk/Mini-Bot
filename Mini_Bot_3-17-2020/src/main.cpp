#include <Arduino.h>
#include <Gyro.h>
#include <SimpleList.h>
#include <Loopable.h>
#include <Schedular.h>
#include <Gyro.h>

//Our gyro with a serial port of Serial1 as that is where it is plugged in
//Gyro gyro(Serial1, 600);
Gyro gyro(Serial1, 600, "gyro");
SimpleList<Loopable *> *schedularList = new SimpleList<Loopable *>();
Schedular *schedular;

void setup()
{

  schedularList->add(&gyro);
  schedular = new Schedular(schedularList);

  //Initalize serial ports.
  Serial.begin(115200);

  while (!Serial)
  {
    /* code */
  }

  //Set serial port timeout to 1 millisecond.
  Serial.setTimeout(1);

  //Notify booting.
  Serial.println("Booting...");

  //Begin waiting for gyro.

  //Notify that the gyro is connected.
  schedular->init();
}

void loop()
{
  schedular->periodic();
  if (!gyro.getIsWatchdogTripped())
    Serial.println(gyro.getYaw());
}
