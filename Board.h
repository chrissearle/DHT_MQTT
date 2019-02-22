#ifndef BOARD_H
#define BOARD_H

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <PubSubClient.h>

#include "Sensor.h"

class Board
{
private:
  PubSubClient *pubSubClient;
  Sensor *sensorList[5];
  byte sensorCount = 0;
  char *clientName;

  void reconnect();

public:
  Board(char *name, Client &client);

  void addSensor(Sensor *sensor);

  void publish();

  void keepAlive();
};

#endif
