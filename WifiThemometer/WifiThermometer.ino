#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define STASSID  ""
#define STAPSK   ""
#define DESTHOST "192.168.0.7"
#define DESTPORT 4444

#define ONE_WIRE_BUS 0

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

WiFiUDP Udp;

void setup() {
  Serial.begin(9600);
  sensors.begin();

  WiFi.mode(WIFI_STA);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);
  Serial.println(temperature);

  char buf[6];
  sprintf(buf, "%s %.2f\n", WiFi.localIP().toString().c_str(), temperature);

  Udp.beginPacket(DESTHOST, DESTPORT);
  Udp.write(buf);
  Udp.endPacket();

  delay(1000);
}
