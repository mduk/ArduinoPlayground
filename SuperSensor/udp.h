#pragma once

#include <PolledTimeout.h>
#include <WiFiUdp.h>

#include "sensors.h"

namespace udp {

  WiFiUDP Udp;

  void setup() {
  }

  void loop() {
    sensordata readings = sensors::read();

    Udp.beginPacket(UDP_DESTHOST, UDP_DESTPORT);
    Udp.println(readings.c);
    Udp.endPacket();
  }

}
