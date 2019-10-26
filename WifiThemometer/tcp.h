#pragma once

#include <PolledTimeout.h>
#include <ESP8266WiFi.h>

#include "dallastemp.h"

namespace tcp {

  WiFiClient client;

  void setup() {
    client.connect(TCP_DESTHOST, TCP_DESTPORT);
  }

  void loop() {
    if (!client.connected()) {
      client.connect(TCP_DESTHOST, TCP_DESTPORT);
    }

    client.println(dallastemp::temperature().c_str());
  }

}
