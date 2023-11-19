const int trigPin = 9;
const int echoPin = 10;
const int ldrPin = A0;

const int rgbRedPin = 6;
const int rgbGreenPin = 5;
const int rgbBluePin = 3;

// variabile pentru stocarea valorilor RGB
int manualRedValue = 0;
int manualGreenValue = 0;
int manualBlueValue = 0;

bool automaticMode = false;  // indicator pentru modul automat

int savedRedValue = 0;
int savedGreenValue = 0;
int savedBlueValue = 0;

int ultrasonicThreshold = 0;
bool ultrasonicAlert = false;

int ldrThreshold = 500;
bool ldrAlert = false;

bool inResetLoggerDataConfirmation = false;
int samplingInterval = 0; 

// varibile pentru vectorii care memoreaza cele 10 valori
const int bufferSize = 10;
int ultrasonicReadings[bufferSize];
int ldrReadings[bufferSize];
int currentIndex = 0;

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);

  pinMode(rgbRedPin, OUTPUT);
  pinMode(rgbGreenPin, OUTPUT);
  pinMode(rgbBluePin, OUTPUT);

  pinMode(ldrPin, INPUT);

  Serial.begin(9600);
  printMenu();
}

void loop() {
  if (Serial.available() > 0) {
    int userChoice = Serial.read() - '0';
    if (!inResetLoggerDataConfirmation) {
      if (userChoice == 5) {
        CurrentSensorReadings();
      } else {
        printMessage(userChoice);
      }
    } else {
      processResetLoggerDataChoice(userChoice);
    }
  }
   handleAutomaticMode();
}

void printMenu() {
  Serial.println("\nMain Menu:");
  Serial.println("1. Sensor Settings");
  Serial.println("2. Reset Logger Data");
  Serial.println("3. System Status");
  Serial.println("4. RGB LED Control");
}

void printMessage(int option) {
  switch (option) {
    case 1:
      printSensorSettingsMenu();
      break;
    case 2:
      startResetLoggerDataConfirmation();
      break;
    case 3:
      printSystemStatusMenu();
      break;
    case 4:
      printRGBLEDControlOption();
      break;
    default:
      Serial.println("Invalid Option. Please try again.");
      printMenu();
  }
}

//1. Sensor Settings
void printSensorSettingsMenu() {
  Serial.println("1. Sensor Settings:");
  Serial.println("  1. Sensors Sampling Interval");
  Serial.println("  2. Ultrasonic Alert Threshold");
  Serial.println("  3. LDR Alert Threshold");
  Serial.println("  4. Back");
  while (Serial.available() == 0) {
    // Așteaptă introducerea utilizatorului
  }
  int subOption = Serial.read() - '0';
  processSensorSettingsOption(subOption);
}

void processSensorSettingsOption(int subOption) {
  switch (subOption) {
    case 1:
      SensorsSamplingInterval();
      break;
    case 2:
      UltrasonicAlertThreshold();
      break;
    case 3:
      LDRAlertThreshold();
      break;
    case 4:
      printMenu();
      break;
  }
}

void SensorsSamplingInterval() {
  Serial.println("Sensors Sampling Interval:");
  Serial.println("Enter a value between 1 and 10 seconds:");
  while (Serial.available() == 0) {

  }
  samplingInterval = Serial.parseInt();
  if (samplingInterval >= 1 && samplingInterval <= 10) {
    Serial.print("Sampling interval set to ");
    Serial.print(samplingInterval);
    Serial.println(" seconds.");
  } else {
    Serial.println("Invalid input. Please enter a value between 1 and 10 seconds.");
  }
}

void UltrasonicAlertThreshold() {
  Serial.println("Ultrasonic Alert Threshold:");
  Serial.println("Enter a threshold value for the ultrasonic sensor:");
  while (Serial.available() == 0) {
    
  }
  ultrasonicThreshold = Serial.parseInt();
  Serial.print("Current Ultrasonic Threshold set to: ");
  Serial.println(ultrasonicThreshold);
}

void LDRAlertThreshold() {
  Serial.println("LDR Alert Threshold:");
  Serial.println("Enter a threshold value for the LDR sensor:");
  while (Serial.available() == 0) {
  }
  ldrThreshold = Serial.parseInt();
  Serial.print("Current LDR Threshold set to: ");
  Serial.println(ldrThreshold);
}

//2. Reset Logger Data
void startResetLoggerDataConfirmation() {
  Serial.println("2. Reset Logger Data:");
  Serial.println("  Are you sure you want to reset all data?");
  inResetLoggerDataConfirmation = true;
  Serial.println("  1. YES");
  Serial.println("  2. NO");
}

void processResetLoggerDataChoice(int subOption) {
  switch (subOption) {
    case 1:
      resetData();
      Serial.println("YES. Data reset complete.");
      inResetLoggerDataConfirmation = false;
      break;
    case 2:
      Serial.println("NO. Data reset canceled.");
      inResetLoggerDataConfirmation = false;
      break;
  }
}

void resetData() {
  savedRedValue = 0;
  savedGreenValue = 0;
  savedBlueValue = 0;
  samplingInterval = 0;
  ultrasonicThreshold = 0;
  ldrThreshold = 500;
  ultrasonicAlert = false;
  ldrAlert = false;
}

//3. System Status
void printSystemStatusMenu() {
  Serial.println("3. System Status:");
  Serial.println("  1. Current Sensor Readings");
  Serial.println("  2. Current Sensor Settings");
  Serial.println("  3. Display Logged Data");
  Serial.println("  4. Back");
  while (Serial.available() == 0) {

  }
  int subOption = Serial.read() - '0';
  processSystemStatusOption(subOption);
}

void processSystemStatusOption(int subOption) {
  switch (subOption) {
    case 1:
      CurrentSensorReadings();
      break;
    case 2:
      displayCurrentSensorSettings();
      break;
    case 3:
      displayRecentSensorReadings();
      break;
    case 4:
      printMenu();
      break;
  }
}

void printSensorReadings() {
  int ultrasonicValue = readUltrasonicSensor();
  int ldrValue = analogRead(ldrPin);

  ultrasonicReadings[currentIndex] = ultrasonicValue;
  ldrReadings[currentIndex] = ldrValue;
  currentIndex = (currentIndex + 1) % bufferSize;

  Serial.print("Ultrasonic Sensor Value: ");
  Serial.println(ultrasonicValue);
  
  Serial.print("LDR Sensor Value: ");
  Serial.println(ldrValue);
}

void CurrentSensorReadings() {
  Serial.println("Current Sensor Readings:");
  Serial.println("Press 'A or a' to stop readings.");

  while (!Serial.available()) {
    printSensorReadings();   // afiseaza continuu citirile senzorilor la rata de esantionare setata
    if (Serial.available()) {
      char userInput = Serial.read();
      if (userInput == 'A' || userInput == 'a') {
        break;               
      }
    }
    delay(samplingInterval * 1000);  // asteapta intervalul de esantionare
  }
  // curata buffer-ul serial pentru a evita citirea neasteptata
  while (Serial.available()) {
    Serial.read();
  }
  Serial.println("Stopped sensor readings.");
  printMenu();  
}

void displayCurrentSensorSettings() {
  Serial.println("Current Sensor Settings:");
  Serial.print("Sampling Interval: ");
  Serial.print(samplingInterval);
  Serial.println(" seconds");

  Serial.print("Ultrasonic Alert Threshold: ");
  Serial.println(ultrasonicThreshold);

  Serial.print("LDR Alert Threshold: ");
  Serial.println(ldrThreshold);
}

void displayRecentSensorReadings() {
  Serial.println("Recent Sensor Readings:");

  for (int i = 0; i < bufferSize; i++) {
    int index = (currentIndex + i) % bufferSize;
    
    Serial.print("Ultrasonic Reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(ultrasonicReadings[index]);

    Serial.print("LDR Reading ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(ldrReadings[index]);
  }
}

//4. RGB LED Control
void printRGBLEDControlOption() {
  Serial.println("4. RGB LED Control:");
  Serial.println("  1. Manual Color Control");
  Serial.println("  2. LED: Toggle Automatic ON/OFF");
  Serial.println("  3. Back");
  while (Serial.available() == 0) {
    
  }
  int subOption = Serial.read() - '0';
  processRGBLEDControlOption(subOption);
}

void processRGBLEDControlOption(int subOption) {
  switch (subOption) {
    case 1:
      processManualColorControl();
      break;
    case 2:
      toggleAutomaticMode();
      break;
    case 3:
      printMenu();
      break;
  }
}

void processManualColorControl() {
  Serial.println("Manual Color Control:");
  Serial.println("Enter RGB values (0-255) separated by commas (e.g.: 255,0,0 for red; 0,255,0 for green; 0,0,255 for red):");
  while (Serial.available() == 0) {
 
  }
  String input = Serial.readStringUntil('\n');    // citeste input-ul utilizatorului
  // descompune input-ul în componente Red, Green si Blue
  int commaIndex1 = input.indexOf(',');
  int commaIndex2 = input.indexOf(',', commaIndex1 + 1);
  if (commaIndex1 != -1 && commaIndex2 != -1) {
    // extrage valorile Red, Green si Blue
    manualRedValue = input.substring(0, commaIndex1).toInt();
    manualGreenValue = input.substring(commaIndex1 + 1, commaIndex2).toInt();
    manualBlueValue = input.substring(commaIndex2 + 1).toInt();
    // seteaza culoarea LED-ului la valorile manual introduse
    setColor(manualRedValue, manualGreenValue, manualBlueValue);
  } else {
    Serial.println("Invalid input format. Please enter RGB values separated by commas.");
  }
}

void toggleAutomaticMode() {
  automaticMode = !automaticMode;
  if (automaticMode) {
    Serial.println("Automatic Mode: ON");
  } else {
    Serial.println("Automatic Mode: OFF");
    setColor(savedRedValue, savedGreenValue, savedBlueValue);  // daca modul automat este dezactivat, utilizeaza ultimele valori salvate pentru culoarea LED-ului
  }
}

void handleAutomaticMode() {
  if (automaticMode) {
    // verifica daca oricare dintre senzori depaseste pragul
    int ultrasonicAlertStatus = checkUltrasonicAlert();
    int ldrAlertStatus = checkLDRAlert();
    handleAlertAndLED(ultrasonicAlertStatus, ldrAlertStatus);
  }
}

int checkUltrasonicAlert() {
  int sensorValue = readUltrasonicSensor();
  if (sensorValue < ultrasonicThreshold) {
    ultrasonicAlert = true;
    return 1;  // alerta: Obiect prea aproape
  } else {
    ultrasonicAlert = false;
    return 0;  // fara alerta
  }
}

int checkLDRAlert() {
  int ldrValue = analogRead(ldrPin);
  if (ldrValue < ldrThreshold) {
    ldrAlert = true;
    return 1;  // alerta: lumina scazuta (potential noapte)
  } else {
    ldrAlert = false;
    return 0;  // fara alerta
  }
}

void handleAlertAndLED(int ultrasonicAlertStatus, int ldrAlertStatus) {
  if (ultrasonicAlertStatus == 1 || ldrAlertStatus == 1) {
    if (ultrasonicAlert) {
      Serial.println("Alert: Object too close!");
    } else if (ldrAlert) {
      Serial.println("Alert: Low light condition (potential night)!");
    }
    setColor(255, 0, 0);  // seteaza culoarea LED-ului la ROȘU
  } else {
    setColor(0, 255, 0);  // seteaza culoarea LED-ului la VERDE dacă nu există alerta
  }
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(rgbRedPin, redValue);
  analogWrite(rgbGreenPin, greenValue);
  analogWrite(rgbBluePin, blueValue);

  savedRedValue = redValue;
  savedGreenValue = greenValue;
  savedBlueValue = blueValue;
}

int readUltrasonicSensor() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);  
  int distance = duration * 0.034 / 2;     
  return distance;
}
