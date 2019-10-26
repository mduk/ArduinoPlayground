#pragma once

namespace adc {
  int reading = 0;

  void setup() {
  }

  void loop() {
    reading = analogRead(A0);
  }

  int getReading() {
    return reading;
  }

  String getReadingString() {
    char buf[6];
    sprintf(buf, "%d", reading);

    return String(buf);
  }
}
