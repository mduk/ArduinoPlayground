#define VALVE_PIN          3
#define SENSOR_PIN         2
#define SENSOR_INTERRUPT   0
#define CALIBRATION_FACTOR 4.5

volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

void setup()
{
  Serial.begin(38400);

  pinMode(SENSOR_PIN, INPUT);
  digitalWrite(SENSOR_PIN, HIGH);

  pinMode(VALVE_PIN, OUTPUT);
  digitalWrite(VALVE_PIN, LOW);

  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;

  attachInterrupt(SENSOR_INTERRUPT, pulseCounter, FALLING);
}

void loop()
{
  if((millis() - oldTime) > 1000)    // Only process counters once per second
  {
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

  if (Serial.available()) {
    char c = Serial.read();
    switch (c) {
      case ' ':
        open();
        totalMilliLitres = 0;
        break;

      case 'o': open(); break;
      case 'c': close(); break;
    }
  }

  if (totalMilliLitres > 2000) {
    digitalWrite(VALVE_PIN, LOW);
  }
}

void pulseCounter()
{
  pulseCount++;
}

void open() {
  digitalWrite(VALVE_PIN, HIGH);
}

void close() {
  digitalWrite(VALVE_PIN, LOW);
}
