#define VALVE_PIN          3

void valve_setup() {
  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);
}

void valve_open() {
  digitalWrite(VALVE_PIN, HIGH);
}

void valve_close() {
  digitalWrite(VALVE_PIN, LOW);
}
