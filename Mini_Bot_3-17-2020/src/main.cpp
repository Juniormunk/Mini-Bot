#include <Arduino.h>
#include <Gyro.h>
#include <SimpleList.h>
#include <Loopable.h>
#include <Schedular.h>
#include <SoftwareSerialTicker.h>
#include <HardwareSerialTicker.h>
#include <MotorController.h>

//Our gyro with a serial port of Serial1 as that is where it is plugged in
//Gyro gyro(Serial1, 600);
HardwareSerialTicker hardSerialTicker(Serial1, "Hardware Serial Ticker");
Gyro gyro(600, "gyro", &hardSerialTicker);
//SoftwareSerialTicker softSerialTicker(Serial, "Software Serial Ticker");
MotorController leftWheel("Left Wheel", 30, 31, 32);

SimpleList<Loopable *> *schedularList = new SimpleList<Loopable *>();
Schedular *schedular;

void setup()
{
  schedularList->add(&hardSerialTicker);
  //schedularList->add(&softSerialTicker);
  schedularList->add(&gyro);
  schedularList->add(&leftWheel);
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

  schedular->init();
}

void loop()
{
  schedular->periodic();
  if (!gyro.getIsWatchdogTripped())
    Serial.println(gyro.getYaw());
  leftWheel.setOutput(.5);
}
