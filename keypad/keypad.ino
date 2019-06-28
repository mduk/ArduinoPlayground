#include <Keypad.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

const char  keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
  { '1', '4', '7', '*' },
  { '2', '5', '8', '0' },
  { '3', '6', '9', '#' },
  { 'A', 'B', 'C', 'D' }
};

const char kp_row_pins[KEYPAD_ROWS] = { A3, A2, A1, A0 };
const char kp_col_pins[KEYPAD_COLS] = { 13, 12, 11, 10 };

Keypad keypad = Keypad(makeKeymap(keymap),
                   kp_row_pins, kp_col_pins,
                   KEYPAD_ROWS, KEYPAD_COLS);


void setup() {
  Serial.begin(9600);
  Serial.println("Ready.");
  Serial.println();
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
  }
}
