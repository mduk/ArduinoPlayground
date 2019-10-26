#pragma once

#include <Wire.h>
#include <MAX44009.h>

namespace light {

  MAX44009 light;

  void setup() {
    if(light.begin()) {
      Serial.println("Could not find a valid MAX44009 sensor, check wiring!");
    }
  }

  void loop() {
    Serial.print("Light (lux):    ");
    Serial.println(light.get_lux());
  }
}
