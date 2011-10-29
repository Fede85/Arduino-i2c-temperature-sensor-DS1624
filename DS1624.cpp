/*
  Library for controlling the DS1624 ic with Arduino
  Tested with arduino-1.0 rc1

  26/03/2010 Release 0.1 (compliant only with 0022 or older)
  Written by Federico and Riccardo Galli  
  http://www.sideralis.org

  Revised to reach the Arduino 1.0 standards by:
  Federico Vanzati / f.vanzati@gmail.com
*/

#include "Arduino.h"
#include "DS1624.h"
#include <Wire.h>

DS1624::DS1624(int8_t addr)
{
  this->addr=addr;
  Wire.begin();
}

void DS1624::start()
{
    Wire.beginTransmission(this->addr);
    Wire.write((uint8_t)0xAC);
    Wire.write(CONTINUOUS_CONVERSION); //Put the DS1624 in continuos conversion mode
    Wire.endTransmission();
    delay (100); //Min time needed to store the previous command is 10ms
    Wire.beginTransmission(this->addr);
    Wire.write(CONVERT_T); //Enable the continuos conversion mode
    Wire.endTransmission();
}

float DS1624::getTemp()
{
  float temperature = 0;
  int tempmsb = 0;
  int templsb = 0;
  int temp2 = 0;

  Wire.beginTransmission(this->addr);
  Wire.write(READ_T);
  Wire.requestFrom(this->addr, 2);

  if (Wire.available()) {
    tempmsb = Wire.read();
  }
  if (Wire.available()) {
    templsb = Wire.read();
  }
  temp2 = templsb >> 3;
  temperature = (float(tempmsb) + (float(temp2) * 0.03125));
  Wire.endTransmission();
  return temperature;
}
