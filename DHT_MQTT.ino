#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>

#include "Configuration.h"

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

#if BOARD == LOUNGE
const char *deviceName = "lounge";
const char *sensor1 = "lounge";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == BEDROOM
const char *deviceName = "bedroom";
const char *sensor1 = "bedroom1";
const char *sensor2 = "hallway";
DHT dht1(D1, DHTTYPE);
DHT dnt2(D2, DHTTYPE);
#define DHT2 1
#endif

#if BOARD == KITCHEN
const char *deviceName = "kitchen";
const char *sensor1 = "kitchen";
const char *sensor2 = "short_hall";
DHT dht1(D1, DHTTYPE);
DHT dht2(D2, DHTTYPE);
#define DHT2 1
#endif

#if BOARD == DINING
const char *deviceName = "dining_room";
const char *sensor1 = "dining_room";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == BEDROOM2
const char *deviceName = "bedroom2";
const char *sensor1 = "bedroom2";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == BEDROOM3
const char *deviceName = "bedroom3";
const char *sensor1 = "bedroom3";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == CELLAR
const char *deviceName = "cellar";
const char *sensor1 = "cellar";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == STORE
const char *deviceName = "stora";
const char *sensor1 = "store_room";
const char *sensor2 = "store_hall";
const char *sensor3 = "workshop";
DHT dht1(D1, DHTTYPE);
DHT dht2(D2, DHTTYPE);
DHT dht3(D3, DHTTYPE);
#define DHT2 1
#define DHT3 1
#endif

#if BOARD == HALL
const char *deviceName = "hall";
const char *sensor1 = "entry_hall";
DHT dht1(D1, DHTTYPE);
#endif

#if BOARD == BATHROOM
const char *deviceName = "bathroom";
const char *sensor1 = "bathroom";
DHT dht1(D1, DHTTYPE);
#endif

#define SENDMQ 1

WiFiClient wifiClient;

#if SENDMQ
PubSubClient client(wifiClient);
#endif

long lastMsg = 0;
char msg[100];

void setup()
{
  Serial.begin(115200);

  WiFiManager wifiManager;

  wifiManager.autoConnect("AutoConnectAP");

#if SENDMQ
  client.setServer(MQTT_SERVER, 1883);
#endif

  dht1.begin();

#if DHT2
  dht2.begin();
#endif

#if DHT3
  dht3.begin();
#endif

  send();
}

void sendFields(const char *name, float temp, float hum)
{
  snprintf(msg, 100, "{ \"location\": \"%s\", \"temperature\": %f, \"humidity\": %f }", name, temp, hum);
  Serial.print("Publish message: ");
  Serial.println(msg);

#if SENDMQ
  client.publish(MQTT_TOPIC, msg);
#else
  Serial.println("MQ not enabled");
#endif
}

void send()
{
  sendFields(sensor1, dht1.readTemperature(), dht1.readHumidity());
#if DHT2
  sendFields(sensor2, dht2.readTemperature(), dht2.readHumidity());
#endif
#if DHT3
  sendFields(sensor3, dht3.readTemperature(), dht3.readHumidity());
#endif
}

#if SENDMQ
void reconnect()
{

  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");

    String clientId = String("Arduino-DHT-" + String(deviceName));

    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
#endif

void loop()
{
#if SENDMQ
  if (!client.connected())
  {
    reconnect();
  }

  client.loop();
#endif

  long now = millis();

  if (now - lastMsg > (60 * 1000))
  {
    lastMsg = now;
    send();
  }
}
