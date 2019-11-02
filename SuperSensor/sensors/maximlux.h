#pragma once

#include <Wire.h>
#include <MAX44009.h>

namespace maximlux {

  MAX44009 light;
  float lux = 0;

  void setup() {
    Wire.begin();

    if (light.begin()) {
      Serial.println("maximlux::setup - Error communicating with MAX44009");
    }
    else {
      Serial.println("maximlux::setup - Sensor started");
    }
  }

  void loop() {
    lux = light.get_lux();
  }

  float getLux() {
    return lux;
  }

  String getLuxString() {
    char buf[6];
    sprintf(buf, "%.2f", lux);

    return String(buf);
  }

}
