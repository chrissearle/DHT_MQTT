#include "Sensor.h"

Sensor::Sensor(char *name, byte pin)
{
    sensor_name = strdup(name);
    sensor_pin = pin;

    dht = new DHT(sensor_pin, DHT22);

    dht->begin();
}

char *Sensor::getName()
{
    return sensor_name;
}

float Sensor::getHumidity()
{
    return dht->readHumidity();
}

float Sensor::getTemperature()
{
    return dht->readTemperature();
}