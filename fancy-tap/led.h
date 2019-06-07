#define STATUS_RED_PIN 11
#define STATUS_GRN_PIN 12

void led_setup() {
  pinMode(STATUS_RED_PIN, OUTPUT);
  digitalWrite(STATUS_RED_PIN, LOW);

  pinMode(STATUS_GRN_PIN, OUTPUT);
  digitalWrite(STATUS_GRN_PIN, LOW);
}

void led_off() {
  digitalWrite(STATUS_RED_PIN, LOW);
  digitalWrite(STATUS_GRN_PIN, LOW);
}

void led_red() {
  digitalWrite(STATUS_RED_PIN, HIGH);
  digitalWrite(STATUS_GRN_PIN, LOW);
}

void led_green() {
  digitalWrite(STATUS_RED_PIN, LOW);
  digitalWrite(STATUS_GRN_PIN, HIGH);
}
