#pragma once

#include <ESP8266WiFi.h>

namespace wifi {

  void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');
      delay(500);
    }
    Serial.print("Connected! IP address: ");
    Serial.println(WiFi.localIP());
  }

  void loop() {
  }

}
