#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include "Board.h"
#include "Sensor.h"

#define DHTTYPE DHT22

#define LOUNGE 0
#define BEDROOM 1
#define DINING 2
#define KITCHEN 3
#define BEDROOM2 4
#define BEDROOM3 5
#define CELLAR 6
#define STORE 7
#define HALL 8
#define BATHROOM 9

#define BOARD DINING

Board *board = NULL;

WiFiClient wifiClient;

long lastMsg = 0;

void setup()
{
  Serial.begin(115200);

  WiFiManager wifiManager;

  wifiManager.autoConnect("AutoConnectAP");

  switch (BOARD)
  {
  case LOUNGE:
    board = new Board("lounge", wifiClient);
    board->addSensor(new Sensor("lounge", D1));
    break;

  case BEDROOM:
    board = new Board("bedroom", wifiClient);
    board->addSensor(new Sensor("bedroom1", D1));
    board->addSensor(new Sensor("hallway", D2));
    break;

  case KITCHEN:
    board = new Board("kitchen", wifiClient);
    board->addSensor(new Sensor("kitchen", D1));
    board->addSensor(new Sensor("short_hall", D2));
    break;

  case DINING:
    board = new Board("dining_room", wifiClient);
    board->addSensor(new Sensor("dining_room", D1));
    break;

  case BEDROOM2:
    board = new Board("bedroom2", wifiClient);
    board->addSensor(new Sensor("bedroom2", D1));
    break;

  case BEDROOM3:
    board = new Board("bedroom3", wifiClient);
    board->addSensor(new Sensor("bedroom3", D1));
    break;

  case CELLAR:
    board = new Board("cellar", wifiClient);
    board->addSensor(new Sensor("cellar", D1));
    break;

  case STORE:
    board = new Board("store", wifiClient);
    board->addSensor(new Sensor("store_room", D1));
    board->addSensor(new Sensor("store_hall", D1));
    board->addSensor(new Sensor("workshop", D1));
    break;

  case HALL:
    board = new Board("hall", wifiClient);
    board->addSensor(new Sensor("entry_hall", D1));
    break;

  case BATHROOM:
    board = new Board("bathroom", wifiClient);
    board->addSensor(new Sensor("bathroom", D1));
    break;
  }
}

void loop()
{
  board->keepAlive();

  long now = millis();

  if (now - lastMsg > (60 * 1000))
  {
    lastMsg = now;
    board->publish();
  }
}
