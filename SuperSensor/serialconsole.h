#include "sensors.h"
#include "mqtt.h"

namespace serialconsole {

  void setup() {
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.print("ESP Chip ID: ");
    Serial.println(ESP.getChipId());
  }

  void loop() {
    if (Serial.available()) {
      char c = Serial.read();

      sensordata readings = sensors::read();
      Serial.println(sensors::asString(readings));
    }
  }

}
