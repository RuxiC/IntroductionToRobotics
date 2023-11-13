const byte latchPin = 11;
const byte clockPin = 10;
const byte dataPin = 12;

const byte segD1 = 4;
const byte segD2 = 5;
const byte segD3 = 6;
const byte segD4 = 7;

const byte lapButtonPin = A0;
const byte startStopButtonPin = A1;
const byte resetButtonPin = A2;

const byte regSize = 8;
byte displayDigits[] = {segD1, segD2, segD3, segD4};
const byte displayCount = 4;
const byte encodingsNumber = 10;

const bool displayOn = LOW;
const bool displayOff = HIGH;

byte byteEncodings[encodingsNumber] = {
    B11111100, // 0
    B01100000, // 1
    B11011010, // 2
    B11110010, // 3
    B01100110, // 4
    B10110110, // 5
    B10111110, // 6
    B11100000, // 7
    B11111110, // 8
    B11110110, // 9
};


byte registers[regSize];

unsigned long totalMilliseconds = 0;
bool isRunning = false;
unsigned long lastMillis = 0;

const byte maxLaps = 4;
unsigned long lapTimes[maxLaps] = {0};
unsigned long savedLapTimes[maxLaps] = {0};
byte currentLap = 0;
bool lapDisplayMode = false;
bool lapButtonPressed = false;


void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
 
  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], displayOff);
  }
 
  pinMode(lapButtonPin, INPUT_PULLUP);
  pinMode(startStopButtonPin, INPUT_PULLUP);
  pinMode(resetButtonPin, INPUT_PULLUP);
 
  displayInitialValue();  // Apelam functia pentru a afisa "000.0" la inceput
  
}
// Functia pentru a afisa "000.0"
void displayInitialValue() {
  for (int i = 0; i < displayCount; i++) {
    byte encoding = byteEncodings[0];
    if (i == 2) {
      bitSet(encoding, 0);
    }
    turnOffDisplays();
    writeReg(encoding);
    turnOnDisplay(i);
    delay(5);
    writeReg(B00000000);
  }
}

void loop() {
  
  bool startStopButtonState = digitalRead(startStopButtonPin);
  bool resetButtonState = digitalRead(resetButtonPin);
  bool lapButtonState = digitalRead(lapButtonPin);

// Functionare buton start/stop
  if (startStopButtonState == LOW) {
    if (!isRunning) {
      isRunning = true;
      lastMillis = millis();
    } else {
      isRunning = false;
    }
  }

// Functionare buton reset
  if (resetButtonState == LOW && !isRunning) {
    // resetam cronometrul si il readucem in starea "000.0"
    lapDisplayMode = false;
    totalMilliseconds = 0;
    writeTime(totalMilliseconds);
    displayInitialValue();
  }

// Functionare buton lap
   if (lapButtonState == LOW && !lapButtonPressed) {
    lapButtonPressed = true;
    if (isRunning) {
      lapTimes[currentLap] = totalMilliseconds;
      currentLap = (currentLap + 1) % maxLaps;
    } else {
      lapDisplayMode = !lapDisplayMode;
    }
  }

  if (lapButtonState == HIGH) {
    lapButtonPressed = false;
  }
  
// Cronometrul
  if (isRunning) {
    unsigned long currentMillis = millis();
    totalMilliseconds += currentMillis - lastMillis;
    lastMillis = currentMillis;

    if (totalMilliseconds >= 999000) { // cronometrul merge pana la "999.9"
      totalMilliseconds = 0;
    }
    if (lapDisplayMode) {
      // afiseaza timpurile salvate
      writeTime(lapTimes[currentLap]);
    } else {
      // afiseaza timpul total
      writeTime(totalMilliseconds / 100);
    }
  }else {
  writeTime(totalMilliseconds/100);
  }
}

void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, MSBFIRST, encoding);
  digitalWrite(latchPin, HIGH);
}

void turnOffDisplays() {
  for (byte i = 0; i < displayCount; i++) {
    digitalWrite(displayDigits[i], displayOff);
  }
}

void turnOnDisplay(byte displayNumber) {
  digitalWrite(displayDigits[displayNumber], displayOn);
}

void writeTime(unsigned int time) {
  byte currentDisplay = 3;

  for (int i = 0; i < 4; i++) {
    byte lastDigit = time % 10;
    byte encoding = byteEncodings[lastDigit];

    if (currentDisplay == 2) {
      bitSet(encoding, 0);
    }
    
    turnOffDisplays();
    writeReg(encoding);
    turnOnDisplay(currentDisplay);
    time /= 10;
    currentDisplay--;
    writeReg(B00000000);
  }
}
