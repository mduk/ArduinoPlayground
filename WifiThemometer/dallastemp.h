#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 0

namespace dallastemp {

  OneWire oneWire(ONE_WIRE_BUS);
  DallasTemperature sensors(&oneWire);

  void setup() {
    sensors.begin();
  }

  void loop() {
    sensors.requestTemperatures();
  }

  String temperature() {
    float temperature = dallastemp::sensors.getTempCByIndex(0);

    char buf[6];
    sprintf(buf, "%.2f", temperature);

    return String(buf);
  }

}
