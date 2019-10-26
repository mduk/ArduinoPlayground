#include <Wire.h>
#include <MAX44009.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 0

MAX44009 light;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void setup() {
    Serial.begin(115200);

    Wire.begin();
    sensors.begin();
    sensors.setResolution(12);

    delay(5000);

    if(light.begin()) {
       Serial.println("Could not find a valid MAX44009 sensor, check wiring!");
    }
}

void loop() {
    sensors.requestTemperatures();
    Serial.print(sensors.getTempCByIndex(0));
    Serial.print("\t");
    Serial.print(light.get_lux());
    Serial.print("\r\n");
    delay(1000);
}
