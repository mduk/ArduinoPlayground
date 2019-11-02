#pragma once

#include <time.h>
#include "ntpclock.h"
#include "sensors/dallastemp.h"
#include "sensors/maximlux.h"
#include "sensors/adc.h"

struct sensordata {
  String time;
  String c;
  String lx;
  int adc;
  String adc_str;
};

namespace sensors {

  sensordata read() {
    sensordata readings;

    readings.time = ntpclock::getTimeString();
    readings.c = dallastemp::getCelciusString();
    readings.lx = maximlux::getLuxString();
    readings.adc = adc::getReading();
    readings.adc_str = adc::getReadingString();

    return readings;
  }

  void setup() {
    dallastemp::setup();
    maximlux::setup();
    adc::setup();
  }

  void loop() {
    dallastemp::loop();
    maximlux::loop();
    adc::loop();
  }

};
