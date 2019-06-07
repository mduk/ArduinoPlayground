#include <Keypad.h>

#define KEYPAD_ROWS 4
#define KEYPAD_COLS 4

const char  keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const char kp_row_pins[KEYPAD_ROWS] = { 7, 8, 9, 10 };
const char kp_col_pins[KEYPAD_COLS] = { 3, 4, 5, 6  };

Keypad keypad = Keypad(makeKeymap(keymap),
                   kp_row_pins, kp_col_pins,
                   KEYPAD_ROWS, KEYPAD_COLS);

