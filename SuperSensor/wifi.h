#pragma once

#include <ESP8266WiFi.h>

namespace wifi {

  void setup() {
    Serial.println("wifi::setup - Connecting to network");
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print('.');

      if (i == 40) {
        Serial.println();
        i = 0;
      }

      delay(500);
    }
    Serial.println();

    Serial.print("wifi::setup - IP address: ");
    Serial.println(WiFi.localIP());
  }

  void loop() {
  }

}
