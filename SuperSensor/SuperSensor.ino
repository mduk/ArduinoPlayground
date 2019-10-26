#include "config.h"
#include "serialconsole.h"
#include "wifi.h"
#include "mdns.h"
#include "ntpclock.h"
#include "webserver.h"

void setup() {
  delay(1000);

  serialconsole::setup();
  wifi::setup();
  mdns::setup();
  ntpclock::setup();
  webserver::setup();
  sensors::setup();
}

void loop() {
  serialconsole::loop();
  wifi::loop();
  mdns::loop();
  ntpclock::loop();
  webserver::loop();
  sensors::loop();
}
