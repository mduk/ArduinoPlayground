#include "config.h"
#include "wifi.h"
#include "mdns.h"
#include "ntpclock.h"
#include "webserver.h"
#include "dallastemp.h"

void setup() {
  Serial.begin(115200);

  wifi::setup();
  mdns::setup();
  ntpclock::setup();
  webserver::setup();
  dallastemp::setup();
}

void loop() {
  wifi::loop();
  mdns::loop();
  ntpclock::loop();
  webserver::loop();
  dallastemp::loop();
}
