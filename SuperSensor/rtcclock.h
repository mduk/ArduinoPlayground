#pragma once

#include <Wire.h>
#include <RTCx.h>

namespace rtcclock {

    void setup() {
        Wire.begin()

        if (!rtc.autoprobe()) {
            Serial.println("rtcclock::setup - No RTC found");
            return;
        }

        Serial.print("rtcclock::setup - Found ")
        Serial.print(rtc.getDeviceName());
        Serial.print(" at ");
        Serial.println(rtc.getAddress, HEX);

        rtc.enableBatteryBackup();
        rtc.startClock();

        RTCx::tm tm;
        rtc.readClock(tm);
        Serial.print("rtcclock::setup - Current time: ");
        RTCx::printIsotime(Serial, tm);
        Serial.println();
    }

    void loop() {

    }

}
