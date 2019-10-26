#include "sensors.h"

namespace serialconsole {

  void setup() {
    Serial.begin(115200);
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

      String l = "<" + readings.time + ">  " + readings.c + "C " + readings.lx + "lx";
      Serial.println(l);
    }
  }

}
