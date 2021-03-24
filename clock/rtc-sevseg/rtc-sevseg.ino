#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <SevSeg.h>

byte digitPins[] = {9, 10, 11, 12};
byte segmentPins[] = {3, 2, 5, 6, 8, 7, 4};

SevSeg sevseg;

void setup() {
  setSyncProvider(RTC.get);   // the function to get the time from the RTC
  if(timeStatus() != timeSet) {
     Serial.println("Unable to sync with the RTC");
  }
  else {
     Serial.println("RTC has set the system time");
  }

  sevseg.begin(
    COMMON_ANODE,
    4, // Number of digits
    digitPins,
    segmentPins,
    false, //resistors on segments
    false, // Update with delays
    true, // leading zeros
    true // disable decimal point
  );
  sevseg.setBrightness(10);
}

void loop() {
  sevseg.setNumber((hour() * 100) + minute());
  sevseg.refreshDisplay();
}
