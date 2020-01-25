#pragma once

#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "sensors.h"

namespace mqtt {
  WiFiClient client;
  Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

  String temp1_feed = String(AIO_USERNAME "/feeds/")
                    + ESP.getChipId()
                    + "-temp1";
  Adafruit_MQTT_Publish temp1    = Adafruit_MQTT_Publish(&mqtt,    temp1_feed.c_str());

  void connect();
  void disconnect();
  void publish();

  void setup() {
  }

  void loop() {
    publish();

    // ping the server to keep the mqtt connection alive
    // NOT required if you are publishing once every KEEPALIVE seconds
    if(!mqtt.ping()) {
     disconnect();
    }
  }

  void publish() {
    connect();

    sensordata readings = sensors::read();

    temp1.publish(readings.c ) && Serial.print(F("mqtt::publish - Temp1 published: ")) && Serial.println(readings.c )
                               || Serial.println(F("mqtt::publish - Temp1 publish failed"));

    disconnect();
  }

  void connect() {
    if (mqtt.connected()) {
      return;
    }

    Serial.print("mqtt::connect - Connecting to broker... ");

    int8_t err;

    uint8_t retries = 3;
    while ((err = mqtt.connect()) != 0) {
         Serial.println(mqtt.connectErrorString(err));
         Serial.println("mqtt::connect - Retrying in 5 seconds...");

         mqtt.disconnect();
         delay(5000);
         retries--;

         if (retries == 0) {
           while (1);
         }
    }

    Serial.println("connected");
  }

  void disconnect() {
    Serial.println("mqtt::disconnect");
    mqtt.disconnect();
  }
}
