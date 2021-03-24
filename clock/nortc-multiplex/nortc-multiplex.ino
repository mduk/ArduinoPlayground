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

int characters[] = {
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

int hours = 0;
int minutes = 0;
int seconds = 0;

unsigned long startMillis;
unsigned long currentMillis;
const unsigned long period = 1000;


void setup() {
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  digitalWrite(digit1, LOW);
  digitalWrite(digit2, HIGH);
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
  digitalWrite(segmentG, LOW);

  startMillis = millis();
}




void tick() {
  currentMillis = millis();
  if (currentMillis - startMillis >= period) {
    seconds++;

    if (seconds == 60) {
      minutes++;
      seconds = 0;
    }

    if (minutes == 60) {
      hours++;
      minutes = 0;
    }

    if (hours == 25) {
      hours = 0;
    }

    startMillis = currentMillis;
  }
}

int displayDigit = 1;

void loop() {
  tick();

  int seconds_tens = seconds / 10;
  int seconds_units = seconds % 10;
  int hours_tens = hours / 10;
  int hours_units = hours % 10;
  int minutes_tens = minutes / 10;
  int minutes_units = minutes % 10;

  switch (displayDigit) {
    case 1: digit(1, minutes_tens); break;
    case 2: digit(2, minutes_units); break;
    case 3: digit(3, seconds_tens); break;
    case 4: digit(4, seconds_units); break;
  }

  displayDigit++;
  if (displayDigit == 5) {
    displayDigit = 1;
  }

  delay(1);
}

void digit(int digit, int value) {
  int index = value;

  if (value > 0) {
    index = value * 7;
  }

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

  digitalWrite(segmentA, !characters[index]);
  digitalWrite(segmentB, !characters[index + 1]);
  digitalWrite(segmentC, !characters[index + 2]);
  digitalWrite(segmentD, !characters[index + 3]);
  digitalWrite(segmentE, !characters[index + 4]);
  digitalWrite(segmentF, !characters[index + 5]);
  digitalWrite(segmentG, !characters[index + 6]);
}


