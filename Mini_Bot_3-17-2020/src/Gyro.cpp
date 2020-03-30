#include "Arduino.h"
#include "Gyro.h"
#include <ErrorCode.h>
#include <SerialReadable.h>
#include <SerialBuffer.h>

ErrorCode Gyro::initialize()
{

    watchdogLastSend = millis();
    while (millis() - watchdogLastSend < 10000) //Wait for the gyro to respond if we have not connected or we are not timed out.
    {
        //Notify the gyro that we are ready.

        println(readySend);

        String response = readString();
        if (response.equals(initializingRecieve))
        {
            Loopable::init();
            return ErrorCode::SUCCESS;
        }
        //We don't need to bombard the gyro with data so we'll take it alittle slow.

        delay(5);
    }
    return ErrorCode::TIMEOUT;
}

void Gyro::init()
{
    Serial.print("Waiting For Gyro...");
    while (true)
    {
        Serial.print(".");
        if (initialize() == ErrorCode::SUCCESS)
        {
            Serial.println("Gyro Connected...");
            return;
        }
    }
    hasInit = true;
    //Loopable::init();
}

void Gyro::periodic()
{
    update();
    updateWatchdog();
}

bool Gyro::isFinished()
{
    return false;
}

void Gyro::end()
{
}

void Gyro::update()
{
    String response = readString();
    if (response.indexOf("Orientation") > -1)
    {
        yaw = getValue(response, ':', 1).toFloat();
    }
    if (response.indexOf(watchDogRecieve) > -1)
    {
        watchdogLastRecieve = millis();
    }
}

bool Gyro::getIsWatchdogTripped()
{
    if (millis() - watchdogLastRecieve > timeout)
        return true;
    return false;
}

void Gyro::updateWatchdog()
{

    if (millis() - watchdogLastSend > 200)
    {
        watchdogLastSend = millis();
        println(watchDogSend);
    }
}

float Gyro::getYaw()
{
    return yaw;
}

float Gyro::getValue()
{
    return getYaw();
}

String Gyro::getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = {0, -1};
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++)
    {
        if (data.charAt(i) == separator || i == maxIndex)
        {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i + 1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}