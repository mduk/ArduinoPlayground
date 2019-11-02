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

      int adc_percent = map(readings.adc, 0, 1024, 0, 100);

      String l = "<" + readings.time + ">  "
               + readings.c + "C "
               + readings.lx + "lx "
               + String(adc_percent) + "%";

      Serial.println(l);
    }
  }

}
