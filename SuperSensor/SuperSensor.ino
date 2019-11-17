#include "config.h"
#include "serialconsole.h"
#include "wifi.h"
#include "mdns.h"
#include "ntpclock.h"
#include "webserver.h"
#include "udp.h"
#include "tcp.h"
#include "mqtt.h"

void setup() {
  delay(1000);
  Serial.begin(115200);

  serialconsole::setup();
  wifi::setup();
//  mdns::setup();
  ntpclock::setup();
  sensors::setup();

//  webserver::setup();
//  udp::setup();
//  tcp::setup();

  mqtt::setup();
}

void loop() {
  serialconsole::loop();
  wifi::loop();
//  mdns::loop();
  ntpclock::loop();
  sensors::loop();

//  webserver::loop();
//  udp::loop();
//  tcp::loop();

  mqtt::loop();

  delay(INTERVAL);
}
