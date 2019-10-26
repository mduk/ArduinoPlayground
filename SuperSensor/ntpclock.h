#pragma once

#include <time.h>

namespace ntpclock {

  String getTimeString(void) {
    static char acTimeString[32];
    time_t now = time(nullptr);
    ctime_r(&now, acTimeString);
    size_t stLength;
    while (((stLength = strlen(acTimeString))) && ('\n' == acTimeString[stLength - 1])) {
      acTimeString[stLength - 1] = 0; // Remove trailing line break...
    }
    return String(acTimeString);
  }

  time_t getTime() {
    return time(nullptr);
  }

  void setup() {
    configTime((TIMEZONE_OFFSET * 3600), (DST_OFFSET * 3600), "pool.ntp.org", "time.nist.gov", "time.windows.com");

    Serial.println("ntpclock::setup - Waiting for NTP time sync: ");
    time_t now = time(nullptr);   // Secs since 01.01.1970 (when uninitalized starts with (8 * 3600 = 28800)
    while (now < 8 * 3600 * 2) {  // Wait for realistic value
      delay(500);
      Serial.print(".");
      now = time(nullptr);
    }
    Serial.println("");
    Serial.printf("ntpclock::setup - Current time: %s\r\n", getTimeString().c_str());
  }

  void loop() {
  }

}
