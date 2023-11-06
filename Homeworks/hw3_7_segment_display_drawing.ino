const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int numSegments = 8;
const int segmentPins[numSegments] = {12, 10, 9, 8, 7, 6, 5, 4};

bool dpState = HIGH;
int currentSegment = 0;
bool segmentState[numSegments] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};

unsigned long lastBlinkMillis = 0;
unsigned long blinkInterval = 500;

int joystickState = -1;
int joystickCenter = 512;
int joystickDeadZone = 50;

void setup() {
  pinMode(pinSW, INPUT_PULLUP);
  pinMode(pinX, INPUT);
  pinMode(pinY, INPUT);

  for (int i = 0; i < numSegments; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }

  segmentState[7] = HIGH;
  for (int i = 0; i < 7; i++) {
    segmentState[i] = LOW;
  }

  Serial.begin(9600);
}

void handleMovement() {
  int xValue = analogRead(pinX);
  int yValue = analogRead(pinY);

  if (yValue > joystickCenter + joystickDeadZone) {
    if (joystickState != 0) {
      Serial.println("DOWN");
      joystickState = 0;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = (currentSegment + 1) % numSegments;
    }
  } else if (yValue < joystickCenter - joystickDeadZone) {
    if (joystickState != 1) {
      Serial.println("UP");
      joystickState = 1;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = (currentSegment + numSegments - 1) % numSegments;
    }
  } else if (xValue < joystickCenter - joystickDeadZone) {
    if (joystickState != 2) {
      Serial.println("LEFT");
      joystickState = 2;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = (currentSegment + numSegments - 1) % numSegments;
    }
  } else if (xValue > joystickCenter + joystickDeadZone) {
    if (joystickState != 3) {
      Serial.println("RIGHT");
      joystickState = 3;
      digitalWrite(segmentPins[currentSegment], segmentState[currentSegment]);
      currentSegment = (currentSegment + 1) % numSegments;
    }
  } else if (xValue > joystickCenter - joystickDeadZone && xValue < joystickCenter + joystickDeadZone &&
             yValue > joystickCenter - joystickDeadZone && yValue < joystickCenter + joystickDeadZone) {
    if (joystickState != -1) {
      joystickState = -1;
    }
  }

  if (currentSegment == 0 && (joystickState == 0 || joystickState == 2 || joystickState == 3)) {
    segmentState[6] = HIGH;
  } else if (currentSegment == 1 && (joystickState == 0 || joystickState == 2)) {
    segmentState[6] = HIGH;
  } else if (currentSegment == 2 && (joystickState == 0 || joystickState == 2 || joystickState == 1 || joystickState == 3)) {
    segmentState[3] = HIGH;
  } else if (currentSegment == 3 && (joystickState == 1 || joystickState == 2 || joystickState == 3)) {
    segmentState[6] = HIGH;
  } else if (currentSegment == 4 && (joystickState == 1 || joystickState == 3)) {
    segmentState[3] = HIGH;
  } else if (currentSegment == 5 && (joystickState == 0 || joystickState == 3)) {
    segmentState[3] = HIGH;
  } else if (currentSegment == 6 && (joystickState == 0 || joystickState == 1)) {
    segmentState[3] = HIGH;
  } else if (currentSegment == 7 && joystickState == 1) {
    segmentState[7] = HIGH;
  } else {
    segmentState[7] = LOW;
  }
}

void updateDisplay() {
  for (int i = 0; i < numSegments; i++) {
    digitalWrite(segmentPins[i], LOW);
  }

  if (dpState == HIGH) {
    digitalWrite(segmentPins[currentSegment], HIGH);
  }

  for (int i = 0; i < numSegments; i++) {
    if (segmentState[i] == HIGH) {
      digitalWrite(segmentPins[i], HIGH);
    }
  }
}

void loop() {
  handleMovement();
  static int lastButtonState = HIGH;
  int buttonState = digitalRead(pinSW);

  if (buttonState == LOW && lastButtonState == HIGH) {
    segmentState[currentSegment] = !segmentState[currentSegment];
  }

  lastButtonState = buttonState;

  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkMillis >= blinkInterval) {
    dpState = !dpState;
    lastBlinkMillis = currentMillis;
  }
  updateDisplay();
}
