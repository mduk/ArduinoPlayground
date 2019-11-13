#include "sensors.h"

namespace serialconsole {

  void setup() {
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
  }

  void loop() {
    if (Serial.available()) {
      char c = Serial.read();

      sensordata readings = sensors::read();
      Serial.println(sensors::asString(readings));
    }
  }

}
