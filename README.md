# DHT22 over MQTT

This is just a simple project for sending DHT22 temperature and humidity data over MQTT.

It's used together with a raspberry pi running MQTT, Node-Red, InfluxDB and Grafana.

## Board

Represents a single Wemos D1 mini and handles MQTT connection. It has a list of connected sensors, and polls them to publish. The data is sent as a string that looks like json (so that the Node-Red json node can convert it to real json).

Set SENDMQ to 0 in Board.cpp to test with connection but without publish

## Sensor

Represents a single sensor.

## Building

You'll need to copy Configuration.h.sample to Configuration.h and set the 4 values there.
