#pragma once

#include <time.h>
#include "ntpclock.h"
#include "sensors/dallastemp.h"
#include "sensors/maximlux.h"
#include "sensors/adc.h"
#include "sensors/humidity.h"

struct sensordata {
  uint32_t chipId;

  time_t time;
  String timeString;

  float c;
  String cString;

  float rh;
  String rhString;

  float lx;
  String lxString;

  int adc;
  String adc_str;
};

namespace sensors {

  sensordata read() {
    sensordata readings;

    readings.chipId = ESP.getChipId();

    readings.time = ntpclock::getTime();
    readings.timeString = ntpclock::getTimeString();

    readings.c = dallastemp::getCelcius(0);
    readings.cString = dallastemp::getCelciusString(0);

    readings.rh = humidity::getRelativeHumidity();
    readings.rhString = humidity::getRelativeHumidityString();

    readings.lx = maximlux::getLux();
    readings.lxString = maximlux::getLuxString();

    readings.adc = adc::getReading();
    readings.adc_str = adc::getReadingString();

    return readings;
  }

  String asString(sensordata readings) {
      int adc_percent = map(readings.adc, 0, 1024, 0, 100);
      return String()
             + readings.chipId + " "
             + readings.time + " "
             + readings.c + "C "
             + readings.rh + "RH "
             + readings.lx + "lx "
             + adc_percent + "%";
  }

  void setup() {
    dallastemp::setup();
    maximlux::setup();
    adc::setup();
    humidity::setup();
  }

  void loop() {
    dallastemp::loop();
    maximlux::loop();
    adc::loop();
    humidity::loop();
  }

}
