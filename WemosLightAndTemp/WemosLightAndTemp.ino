#pragma once

#include "light.h"
#include "temp.h"

void setup() {
  delay(1000);

  Serial.begin(115200);
  Serial.println("setup");

  light::setup();
  temp::setup();
}

void loop() {
  light::loop();
  temp::loop();

  delay(1000);
}
