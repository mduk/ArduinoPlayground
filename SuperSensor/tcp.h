#pragma once

#include <PolledTimeout.h>
#include <ESP8266WiFi.h>

#include "sensors.h"

namespace tcp {

  WiFiClient client;

  void setup() {
    client.connect(TCP_DESTHOST, TCP_DESTPORT);
  }

  void loop() {
    if (!client.connected()) {
      client.connect(TCP_DESTHOST, TCP_DESTPORT);
    }

    sensordata readings = sensors::read();
    client.println(readings.c);
  }

}
