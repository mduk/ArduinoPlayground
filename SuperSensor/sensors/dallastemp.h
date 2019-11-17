#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 0

namespace dallastemp {

  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  void setup() {
    pinMode(D8, OUTPUT);
    digitalWrite(D8, LOW);

    sensors.begin();
  }

  void loop() {
    sensors.requestTemperatures();
  }

  float getCelcius(int sensor) {
    return sensors.getTempCByIndex(sensor);
  }

  String getCelciusString(int sensor) {
    float temperature = getCelcius(sensor);

    char buf[6];
    sprintf(buf, "%.2f", temperature);

    return String(buf);
  }

}
