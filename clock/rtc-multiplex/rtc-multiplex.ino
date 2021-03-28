#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>


int digit1 = 9 ;
int digit2 = 10;
int digit3 = 11;
int digit4 = 12;

int segmentA = 3;
int segmentB = 2;
int segmentC = 5;
int segmentD = 6;
int segmentE = 8;
int segmentF = 7;
int segmentG = 4;

byte characters[] = {
//   ABCDEFG
  0b01111110, // 0
  0b00110000, // 1
  0b01101101, // 2
  0b01111001, // 3
  0b00110011, // 4
  0b01011011, // 5
  0b01011111, // 6
  0b01110000, // 7
  0b01111111, // 8
  0b01111011, // 9
};

int last_hour;
int last_minute;
int last_second;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  setSyncProvider(RTC.get);

  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);

  pinMode(segmentA, OUTPUT);
  pinMode(segmentB, OUTPUT);
  pinMode(segmentC, OUTPUT);
  pinMode(segmentD, OUTPUT);
  pinMode(segmentE, OUTPUT);
  pinMode(segmentF, OUTPUT);
  pinMode(segmentG, OUTPUT);

  digitalWrite(segmentA, HIGH);
  digitalWrite(segmentB, HIGH);
  digitalWrite(segmentC, HIGH);
  digitalWrite(segmentD, HIGH);
  digitalWrite(segmentE, HIGH);
  digitalWrite(segmentF, HIGH);
  digitalWrite(segmentG, HIGH);

  last_hour = hour();
  last_minute = minute();
  last_second = second();
}

int displayDigit = 1;

void loop() {
  if (Serial.available()) {
    String settimestr = Serial.readString();
    int setyear, setmonth, setday,
        sethour, setminute, setsecond;

    sscanf(
      settimestr.c_str(), "%d-%d-%d_%d:%d:%d",
      &setyear, &setmonth, &setday,
      &sethour, &setminute, &setsecond
    );

    tmElements_t settime;
    settime.Year = setyear;
    settime.Month = setmonth;
    settime.Day = setday;
    settime.Hour = sethour;
    settime.Minute = setminute;
    settime.Second = setsecond;
    RTC.write(settime);

    setTime(
      sethour, setminute, setsecond,
      setday, setmonth, setyear
    );
  }

  int now_hour = hour();
  int now_minute = minute();
  int now_second = second();

  int display_digit1 = charSegments(now_hour   / 10); // Hour Tens
  int display_digit2 = charSegments(now_hour   % 10); // Hour Units
  int display_digit3 = charSegments(now_minute / 10); // Minute Tens
  int display_digit4 = charSegments(now_minute % 10); // Minute Units

  switch (displayDigit) {
    case 1: setDigit(1); setSegments(display_digit1); break;
    case 2: setDigit(2); setSegments(display_digit2); break;
    case 3: setDigit(3); setSegments(display_digit3); break;
    case 4: setDigit(4); setSegments(display_digit4); break;
  }

  displayDigit++;
  if (displayDigit == 5) {
    displayDigit = 1;
  }

  delay(1);

  last_hour = now_hour;
  last_minute = now_minute;
  last_second = now_second;
}

byte mask(int step, byte segments) {
  byte mask = 0;

  switch (step) {
    default: mask = 0b11111111; break;
    case 55: mask = 0b10111111; break;
    case 56: mask = 0b10011101; break;
    case 57: mask = 0b10011100; break;
    case 58: mask = 0b10001000; break;
    case 59: mask = 0b10000000; break;
  }

  return segments & mask;
}

byte charSegments(int value) {
  return characters[value];
}

void setDigit(int digit) {
  switch (digit) {
    case 1:
      digitalWrite(digit1, HIGH);
      digitalWrite(digit2, LOW);
      digitalWrite(digit3, LOW);
      digitalWrite(digit4, LOW);
      break;

    case 2:
      digitalWrite(digit1, LOW);
      digitalWrite(digit2, HIGH);
      digitalWrite(digit3, LOW);
      digitalWrite(digit4, LOW);
      break;

    case 3:
      digitalWrite(digit1, LOW);
      digitalWrite(digit2, LOW);
      digitalWrite(digit3, HIGH);
      digitalWrite(digit4, LOW);
      break;

    case 4:
      digitalWrite(digit1, LOW);
      digitalWrite(digit2, LOW);
      digitalWrite(digit3, LOW);
      digitalWrite(digit4, HIGH);
      break;
  }
}

void setSegments(byte segments) {
  digitalWrite(segmentA, !((segments >> 6 ) & 1));
  digitalWrite(segmentB, !((segments >> 5 ) & 1));
  digitalWrite(segmentC, !((segments >> 4 ) & 1));
  digitalWrite(segmentD, !((segments >> 3 ) & 1));
  digitalWrite(segmentE, !((segments >> 2 ) & 1));
  digitalWrite(segmentF, !((segments >> 1 ) & 1));
  digitalWrite(segmentG, !((segments      ) & 1));
}
