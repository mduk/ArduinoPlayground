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
//A B C D E F G
  1,1,1,1,1,1,0, // 0
  0,1,1,0,0,0,0, // 1
  1,1,0,1,1,0,1, // 2
  1,1,1,1,0,0,1, // 3
  0,1,1,0,0,1,1, // 4
  1,0,1,1,0,1,1, // 5
  1,0,1,1,1,1,1, // 6
  1,1,1,0,0,0,0, // 7
  1,1,1,1,1,1,1, // 8
  1,1,1,1,0,1,1, // 9
};

int last_hour;
int last_minute;
int last_second;


void setup() {
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
  int now_hour = hour();
  int now_minute = minute();
  int now_second = second();

  int hours_tens = now_hour / 10;
  int hours_units = now_hour % 10;
  int minutes_tens = now_minute / 10;
  int minutes_units = now_minute % 10;

  switch (displayDigit) {
    case 1: setDigit(1); setSegments(hours_tens); break;
    case 2: setDigit(2); setSegments(hours_units); break;
    case 3: setDigit(3); setSegments(minutes_tens); break;
    case 4: setDigit(4); setSegments(minutes_units); break;
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

void setSegments(int value) {
  int index = value;

  if (value > 0) {
    index = value * 7;
  }

  digitalWrite(segmentA, !characters[index]);
  digitalWrite(segmentB, !characters[index + 1]);
  digitalWrite(segmentC, !characters[index + 2]);
  digitalWrite(segmentD, !characters[index + 3]);
  digitalWrite(segmentE, !characters[index + 4]);
  digitalWrite(segmentF, !characters[index + 5]);
  digitalWrite(segmentG, !characters[index + 6]);
}


