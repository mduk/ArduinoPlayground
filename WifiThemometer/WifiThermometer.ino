#include <WiFiUdp.h>

#include "config.h"
#include "wifi.h"
#include "udp.h"
#include "tcp.h"
#include "dallastemp.h"

void setup() {
  Serial.begin(9600);

  wifi::setup();
  dallastemp::setup();

  //udp::setup();
  tcp::setup();
}

void loop() {
  wifi::loop();
  dallastemp::loop();

  static esp8266::polledTimeout::periodicMs timeout(INTERVAL);
  if (!timeout.expired()) {
    return;
  }

  //udp::loop();
  tcp::loop();
}
