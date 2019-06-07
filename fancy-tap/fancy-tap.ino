#define STATE_CLOSED       0
#define STATE_OPEN         1

#include "led.h"
#include "lcd.h"
#include "sensor.h"
#include "valve.h"
#include "keypad.h"

uint8_t state = 0;

unsigned long dispense_ml = 0;

void set_state(uint8_t new_state) {
  Serial.print("set_state: ");
  Serial.print(state);
  Serial.print(" => ");
  Serial.println(new_state);

  lcd.clear();

  switch (new_state) {
    case STATE_OPEN:
      Serial.println("Opening Valve");

      led_green();
      valve_open();
      break;

    case STATE_CLOSED:
      Serial.println("Closing Valve. Awaiting Input.");

      led_red();
      valve_close();

      dispense_ml = 0;
      totalMilliLitres = 0;
      break;
  }

  state = new_state;
}

void loop_open() {
  read_sensor();

  if (Serial.available() ) {
    totalMilliLitres += ((Serial.read() - '0') * 100);
  }

  if (dispense_ml > 0 && totalMilliLitres >= dispense_ml) {
    set_state(STATE_CLOSED);
    return;
  }

  char key = keypad.getKey();
  if (key != NO_KEY) {
    set_state(STATE_CLOSED);
  }
}

void loop_closed() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.println();
    Serial.print("Key Pressed: ");
    Serial.println(key);

    switch (key) {

      case '*':
        dispense_ml = 0;
        totalMilliLitres = 0;
        break;

      case '#':
        set_state(STATE_OPEN);
        break;

      case 'A':
        dispense_ml = 10000;
        totalMilliLitres = 0;
        set_state(STATE_OPEN);
        break;

      case 'B':
        dispense_ml = 7000;
        totalMilliLitres = 0;
        set_state(STATE_OPEN);
        break;

      case 'C':
      case 'D':
        Serial.print("Key has no function: ");
        Serial.println(key);
        break;

      default:
        if (state == STATE_CLOSED) {
          dispense_ml = (dispense_ml * 10) + (key - '0');
          Serial.print("dispense_ml: ");
          Serial.println(dispense_ml);
        }
        break;

    }
  }
}


void setup() {
  Serial.begin(9600);

  led_setup();
  lcd_setup();
  valve_setup();
  sensor_setup();

  set_state(STATE_CLOSED);
}

void loop() {
  switch (state) {
    case STATE_OPEN:
      loop_open();
      update_lcd_open(dispense_ml, totalMilliLitres);
      break;

    case STATE_CLOSED:
      loop_closed();
      update_lcd_closed(dispense_ml);
      break;
  }
}
