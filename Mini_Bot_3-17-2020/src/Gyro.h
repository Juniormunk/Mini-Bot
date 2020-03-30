#ifndef Gyro1_h
#define Gyro1_h

#include <Arduino.h>
#include <PIDSensor.h>
#include <ErrorCode.h>
#include <Watchdogable.h>
#include <Loopable.h>
#include <SerialBuffer.h>
#include <SerialReadable.h>

class Gyro : public Loopable, public Watchdogable, public PIDSensor, public SerialReadable
{
public:
    Gyro(unsigned long timeout, String name, SerialBuffer *serialBuffer) : Loopable(), Watchdogable(), PIDSensor(), SerialReadable(serialBuffer)
    {
        this->timeout = timeout;
        //Save the serial away this is where our gyro is connected.
        this->name = name;
    }

    void init();
    void periodic();
    void end();
    bool isFinished();

    float getYaw();         //Returns the yaw.
    float getPitch();       //returns the pitch.
    float getRoll();        //Returns the roll.
    ErrorCode initialize(); //Will run until successfully initialized (10 second timeout)

    void update();
    bool getIsWatchdogTripped(); //Returns if the watchdog has been tripped (AKA: device is not responding.)
    void updateWatchdog();       //Send an update message to the gyro to see if it is responding.
    float getValue();            //Returns the value needed to calculate pid.

private:
    const String readySend = "Ready";
    const String watchDogSend = "WatchDog";
    const String watchDogRecieve = "WatchDog\r";
    const String initializingRecieve = "Initializing...\r";
    String getValue(String data, char separator, int index);
    float yaw;
    float pitch;
    float roll;
};

#endif