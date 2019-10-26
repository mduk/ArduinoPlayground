#pragma once

#include <PolledTimeout.h>
#include <WiFiUdp.h>

#include "dallastemp.h"

namespace udp {

  WiFiUDP Udp;

  void setup() {
  }

  void loop() {
    Udp.beginPacket(UDP_DESTHOST, UDP_DESTPORT);
    Udp.println(dallastemp::temperature().c_str());
    Udp.endPacket();
  }
}
