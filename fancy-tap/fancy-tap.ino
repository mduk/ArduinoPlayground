#include <Keypad.h>

#define VALVE_PIN          13

#define STATUS_RED_PIN     11
#define STATUS_GRN_PIN     12

#define SENSOR_PIN         2
#define SENSOR_INTERRUPT   0
#define CALIBRATION_FACTOR 4.5

#define KEYPAD_ROWS        4
#define KEYPAD_COLS        4

bool do_sensor = true;

const char  keymap[KEYPAD_ROWS][KEYPAD_COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

const char  kp_row_pins[KEYPAD_ROWS] = { 7, 8, 9, 10 };
const char  kp_col_pins[KEYPAD_COLS] = { 3, 4, 5, 6  };

// Here be dragons

#define STATE_CLOSED 0
#define STATE_OPEN   1

uint8_t state = 0;

Keypad kp = Keypad(makeKeymap(keymap),
                   kp_row_pins, kp_col_pins,
                   KEYPAD_ROWS, KEYPAD_COLS);

volatile byte pulseCount = 0;

float flowRate = 0.0;
unsigned int flowMilliLitres = 0;
unsigned long totalMilliLitres = 0;

unsigned long oldTime = 0;

unsigned long dispense_ml = 0;

void set_state(uint8_t new_state) {
  Serial.print("set_state: ");
  Serial.print(state);
  Serial.print(" => ");
  Serial.println(new_state);

  switch (new_state) {
    case STATE_OPEN:
      Serial.println("Opening Valve");
      digitalWrite(STATUS_RED_PIN, LOW);
      digitalWrite(STATUS_GRN_PIN, HIGH);
      digitalWrite(VALVE_PIN, HIGH);
      break;

    case STATE_CLOSED:
      Serial.println("Closing Valve. Awaiting Input.");
      digitalWrite(STATUS_RED_PIN, HIGH);
      digitalWrite(STATUS_GRN_PIN, LOW);
      digitalWrite(VALVE_PIN, LOW);
      dispense_ml = 0;
      totalMilliLitres = 0;
      break;
  }

  state = new_state;
}

void setup() {
  Serial.begin(9600);

  pinMode(STATUS_RED_PIN, OUTPUT);
  digitalWrite(STATUS_RED_PIN, LOW);

  pinMode(STATUS_GRN_PIN, OUTPUT);
  digitalWrite(STATUS_GRN_PIN, LOW);

  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);

  if (do_sensor) {
    pinMode(SENSOR_PIN, INPUT);
    digitalWrite(SENSOR_PIN, HIGH);

    attachInterrupt(SENSOR_INTERRUPT, pulseCounter, FALLING);
  }

  set_state(STATE_CLOSED);
}

void loop() {
  switch (state) {
    case STATE_OPEN: loop_open(); break;
    case STATE_CLOSED: loop_closed(); break;
  }
}

void loop_open() {
  if(do_sensor && (millis() - oldTime) > 1000) { // Only process counters once per second
    detachInterrupt(SENSOR_INTERRUPT);

    // The hall-effect flow sensor outputs approximately 4.5 pulses per second per
    // litre/minute of flow.
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the CALIBRATION_FACTOR to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / CALIBRATION_FACTOR;

    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();

    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;

    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;

    unsigned int frac;

    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(flowRate);  // Print the integer part of the variable
    Serial.print(".");             // Print the decimal point

    // Determine the fractional part. The 10 multiplier gives us 1 decimal place.
    frac = (flowRate - int(flowRate)) * 10;
    Serial.print(frac, DEC) ;      // Print the fractional part of the variable
    Serial.print("L/min");

    Serial.print("  Flow: ");
    Serial.print(flowMilliLitres);
    Serial.print("mL/Sec");

    Serial.print("  Total: ");
    Serial.print(totalMilliLitres);
    Serial.print("mL");
    Serial.print("\r");

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;

    attachInterrupt(SENSOR_INTERRUPT, pulseCounter, FALLING);
  }

  if (dispense_ml > 0 && totalMilliLitres > dispense_ml) {
    set_state(STATE_CLOSED);
    return;
  }

  char key = kp.getKey();
  if (key != NO_KEY) {
    set_state(STATE_CLOSED);
  }
}

void loop_closed() {
  char key = kp.getKey();
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
        dispense_ml = 70000;
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

void pulseCounter() {
  pulseCount++;
}
