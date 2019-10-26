#pragma once

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

namespace wifi {

  const char* ssid = STASSID;
  const char* password = STAPSK;

  void setup() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }

  void loop() {
  }

}
