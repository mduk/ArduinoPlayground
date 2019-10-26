#pragma once

#include <ESP8266WebServer.h>

#include "sensors.h"

namespace webserver {

  ESP8266WebServer server(HTTP_LISTEN_PORT);

  void handleHTTPRequest() {

    sensordata readings = sensors::read();

    String l = "webserver::handleHTTPRequest - " + readings.time + " " + readings.c + "C " + readings.lx + "lx";
    Serial.println(l);

    String s;

    s = "<!DOCTYPE HTML>\r\n";
    s += "<dl>\r\n";

    s += "<dt>Time</dt>";
    s += "<dd>" + readings.time + "</dd>\r\n";

    s += "<dt>Celcius (DS18B20)</dt>";
    s += "<dd>" + readings.c + "</dd>\r\n";

    s += "<dt>Lux (MAX44009)</dt>";
    s += "<dd>" + readings.lx + "</dd>\r\n";

    s += "</dl>";

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
