#pragma once

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

DHT_Unified dht(DHT_PIN, DHT_TYPE);

namespace humidity {

  sensors_event_t event;

  void setup() {
    dht.begin();
  }

  void loop() {
    dht.humidity().getEvent(&event);
  }

  float getRelativeHumidity() {
    return event.relative_humidity;
  }

  String getRelativeHumidityString() {
    return String(event.relative_humidity);
  }

  float getCelcius() {
    return event.temperature;
  }

  String getCelciusString() {
    return String(event.temperature);
  }

}
