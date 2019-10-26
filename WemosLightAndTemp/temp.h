#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 0

namespace temp {

  OneWire oneWire(ONE_WIRE_BUS);

  DallasTemperature sensors(&oneWire);

  void setup(void) {
    sensors.begin();
    sensors.setResolution(12);
  }

  void loop(void) {
    sensors.requestTemperatures();
    Serial.println(sensors.getTempCByIndex(0));
  }
}
