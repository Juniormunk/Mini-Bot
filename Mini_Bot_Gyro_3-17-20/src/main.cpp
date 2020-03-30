#include <CurieIMU.h>
#include <MadgwickAHRS.h>

Madgwick filter;
Madgwick newFilter;
unsigned long microsPerReading, microsPrevious;
float accelScale, gyroScale;

void initialize()
{
  filter = newFilter;
  CurieIMU.begin();

  CurieIMU.setGyroRate(100);
  CurieIMU.setAccelerometerRate(100);
  filter.begin(100);

  // Set the accelerometer range to 2G
  CurieIMU.setAccelerometerRange(2);

  // Set the gyroscope range to 250 degrees/second
  CurieIMU.setGyroRange(250);
  // use the code below to calibrate accel/gyro offset values
  // Serial.println("Internal sensor offsets BEFORE calibration...");
  // Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getGyroOffset(X_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getGyroOffset(Y_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getGyroOffset(Z_AXIS));
  // Serial.print("\t");
  // Serial.println("");
  //
  // Serial.print("Starting Gyroscope calibration...");
  CurieIMU.autoCalibrateGyroOffset();
  // Serial.println(" Done");
  // Serial.print("Starting Acceleration calibration...");
  CurieIMU.autoCalibrateAccelerometerOffset(X_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Y_AXIS, 0);
  CurieIMU.autoCalibrateAccelerometerOffset(Z_AXIS, 1);
  // Serial.println(" Done");

  // Serial.println("Internal sensor offsets AFTER calibration...");
  // Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(X_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Y_AXIS));
  // Serial.print("\t");
  // Serial.print(CurieIMU.getAccelerometerOffset(Z_AXIS));
  // Serial.print("\t");
  // Serial.println("");
  // initialize variables to pace updates to correct rate
  microsPerReading = 1000000 / 100;
  microsPrevious = micros();
  while (Serial1.available() > 0)
  {
    int charsRead;
    char response[18];

    charsRead = Serial1.readBytesUntil('\n', response, sizeof(response) - 1); //gets bytes until Enter pressed
    response[charsRead] = NULL;                                               // This makes it a string
  }
}

void setup()
{
  Serial1.begin(115200);
  Serial.begin(115200);

  // while (Serial1.available() > 0)
  // {
  //   char t = Serial.read();
  // }
  Serial.setTimeout(5);
  Serial1.setTimeout(5);

  initialize();
  //LEAVE BLANK
  //Set up is in initialize()
}

//
//
//  Gyro Conversions
//
//

float convertRawAcceleration(int aRaw)
{
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767

  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw)
{
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767

  float g = (gRaw * 250.0) / 32768.0;
  return g;
}

void loop()
{
  //Check for any serial commands.
  if (Serial1.available() > 0)
  {
    int charsRead;
    char response[18];

    charsRead = Serial1.readBytesUntil('\n', response, sizeof(response) - 1); //gets bytes until Enter pressed
    response[charsRead] = NULL;                                               // This makes it a string

    char watchDog[] = "WatchDog\r";
    char watchDogResponse[] = "WatchDog";
    char booting[] = "Booting...";
    char initializing[] = "Initializing...";
    char ready[] = "Ready\r";
    // int availableBytes = Serial1.available();

    // If the incoming data is equal to the booting sequence  then reinitialize
    if (strcmp(ready, response) == 0)
    {
      Serial1.println(initializing);
      initialize();
      Serial.println("init");
    }
    //If the incoming data is equal to the watchdog sequence then respond with the watchdog sequence.
    if (strcmp(watchDog, response) == 0)
    {
      Serial1.println(watchDog);
      Serial.println("WatchDog");
    }
  }
  else
  {

    // //
    // //
    // //
    // //GYRO CODE
    // //
    // //
    // //

    int aix, aiy, aiz;
    int gix, giy, giz;
    float ax, ay, az;
    float gx, gy, gz;
    float roll, pitch, heading;
    unsigned long microsNow;

    // check if it's time to read data and update the filter
    microsNow = micros();
    if (microsNow - microsPrevious >= microsPerReading)
    {

      // read raw data from CurieIMU
      CurieIMU.readMotionSensor(aix, aiy, aiz, gix, giy, giz);

      // convert from raw data to gravity and degrees/second units
      ax = convertRawAcceleration(aix);
      ay = convertRawAcceleration(aiy);
      az = convertRawAcceleration(aiz);
      gx = convertRawGyro(gix);
      gy = convertRawGyro(giy);
      gz = convertRawGyro(giz);

      // update the filter, which computes orientation
      filter.updateIMU(gx, gy, gz, ax, ay, az);

      // print the heading, pitch and roll
      roll = filter.getRoll();
      pitch = filter.getPitch();
      heading = filter.getYaw();
      Serial1.print("Orientation: ");
      Serial1.print(heading);
      Serial1.print(" : ");
      Serial1.print(pitch);
      Serial1.print(" : ");
      Serial1.println(roll);

      // increment previous time, so we keep proper pace
      microsPrevious = microsPrevious + microsPerReading;
    }
  }
}
