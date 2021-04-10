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
  0b01110111, // A
  0b00011111, // b
  0b01001110, // C
  0b00111101, // d
  0b01001111, // E
  0b01000111, // F
};

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
}

int display_digit = 1;

byte digit1_segments, digit2_segments,
     digit3_segments, digit4_segments;

int now_hour, now_minute, now_second,
    then_hour, then_minute, then_second;

unsigned long now_second_millis, now_millis;

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

  now_hour = hour();
  now_minute = minute();
  now_second = second();

  if (now_second > then_second) {
    now_second_millis = millis();
    now_millis = now_second_millis;
  }
  else {
    now_millis = millis() - now_second_millis;
  }

  digit1_segments = charSegments(now_hour   / 10); // Hour Tens
  digit2_segments = charSegments(now_hour   % 10); // Hour Units
  digit3_segments = charSegments(now_minute / 10); // Minute Tens
  digit4_segments = charSegments(now_minute % 10); // Minute Units

  switch (display_digit) {
    case 1: setDigit(1); setSegments(digit1_segments); break;
    case 2: setDigit(2); setSegments(digit2_segments); break;
    case 3: setDigit(3); setSegments(digit3_segments); break;
    case 4: setDigit(4); setSegments(digit4_segments); break;
  }

  display_digit++;
  if (display_digit == 5) {
    display_digit = 1;
  }

  delay(1);
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
