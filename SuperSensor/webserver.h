#pragma once

#include <ESP8266WebServer.h>

#include "sensors.h"

namespace webserver {

  ESP8266WebServer server(HTTP_LISTEN_PORT);

  void handleHTTPRequest() {

    sensordata readings = sensors::read();
    String sensorString = sensors::asString(readings);

    String l = "webserver::handleHTTPRequest - " + sensorString;
    Serial.println(l);

    String s;

    s = "<!DOCTYPE HTML>\r\n";
    s += sensorString;
    s += "</html>\r\n\r\n";

    server.send(200, "text/html", s);
  }

  void setup() {
    server.on("/", handleHTTPRequest);
    server.begin();
    Serial.println("webserver::setup - HTTP server started");
  }

  void loop() {
    server.handleClient();
  }

}
