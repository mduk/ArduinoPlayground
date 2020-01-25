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
  sensors::setup();

//  mdns::setup();
//  ntpclock::setup();

//  webserver::setup();
//  udp::setup();
//  tcp::setup();

  mqtt::setup();
}

void loop() {
  serialconsole::loop();
  wifi::loop();
  sensors::loop();

//  mdns::loop();
//  ntpclock::loop();

//  webserver::loop();
//  udp::loop();
//  tcp::loop();

  mqtt::loop();

  delay(INTERVAL);
}
