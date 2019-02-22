#ifndef SENSOR_H
#define SENSOR_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <DHT.h>

class Sensor
{
private:
  char *sensor_name;
  byte sensor_pin;
  DHT *dht;

public:
  Sensor(char *name, byte pin);

  char *getName();
  float getTemperature();
  float getHumidity();
};

#endif
