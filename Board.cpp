
#include <PubSubClient.h>

#include "Board.h"
#include "Sensor.h"
#include "Configuration.h"

#define SENDMQ 1

Board::Board(char *name, Client &client)
{
    clientName = strdup(name);

    pubSubClient = new PubSubClient(client);
    pubSubClient->setServer(MQTT_SERVER, 1883);
}

void Board::reconnect()
{
    while (!pubSubClient->connected())
    {
        Serial.print("Attempting MQTT connection...");

        String clientId = String("Arduino-DHT-" + String(clientName));

        if (pubSubClient->connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD))
        {
            Serial.println("connected");
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(pubSubClient->state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}

void Board::keepAlive()
{
    if (!pubSubClient->connected())
    {
        reconnect();
    }

    pubSubClient->loop();
}

void Board::addSensor(Sensor *sensor)
{
    sensorList[sensorCount] = sensor;
    sensorCount = sensorCount + 1;
}

void Board::publish()
{
    for (int i = 0; i < sensorCount; i++)
    {
        Sensor *sensor = sensorList[i];

        char msg[100];

        snprintf(msg, 100, "{ \"location\": \"%s\", \"temperature\": %f, \"humidity\": %f }", sensor->getName(), sensor->getTemperature(), sensor->getHumidity());
        Serial.print("Publish message: ");
        Serial.println(msg);

#if SENDMQ
        pubSubClient->publish(MQTT_TOPIC, msg);
#else
        Serial.println("MQ not enabled");
#endif
    }
}
