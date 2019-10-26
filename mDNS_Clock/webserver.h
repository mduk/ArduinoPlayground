#pragma once

#include <ESP8266WebServer.h>

#include "ntpclock.h"
#include "dallastemp.h"

namespace webserver {

  ESP8266WebServer              server(SERVICE_PORT);

  void handleHTTPRequest() {
    Serial.println("");
    Serial.println("HTTP Request");

    // Get current time
    time_t now = time(nullptr);;
    struct tm timeinfo;
    gmtime_r(&now, &timeinfo);

    String s;

    s = "<!DOCTYPE HTML>\r\n<html>Hello from ";
    s += WiFi.hostname() + " at " + WiFi.localIP().toString();
    // Simple addition of the current time
    s += "\r\nThe time is ";
    s += ntpclock::getTimeString();
    s += " and it is currently ";
    s += dallastemp::temperature();
    s += " celcius.";
    // done :-)
    s += "</html>\r\n\r\n";
    Serial.println("Sending 200");
    server.send(200, "text/html", s);
  }

  void setup() {
    server.on("/", handleHTTPRequest);
    server.begin();
    Serial.println("HTTP server started");
  }

  void loop() {
    server.handleClient();
  }

}
