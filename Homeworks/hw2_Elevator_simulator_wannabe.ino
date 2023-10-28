const int floor0ButtonPin = 2;  
const int floor1ButtonPin = 3;  
const int floor2ButtonPin = 4;  
const int elevatorMovingLED = 5;  
const int floor0LED = 11;  
const int floor1LED = 12;  
const int floor2LED = 13;  
const int buzzerPin = 9; 

bool isMoving = false;  // Starea curentă a liftului
int currentFloor = 0;  // Etajul curent al liftului

void setup() {
  pinMode(floor0ButtonPin, INPUT_PULLUP);
  pinMode(floor1ButtonPin, INPUT_PULLUP);
  pinMode(floor2ButtonPin, INPUT_PULLUP);
  pinMode(elevatorMovingLED, OUTPUT);
  pinMode(floor0LED, OUTPUT);
  pinMode(floor1LED, OUTPUT);
  pinMode(floor2LED, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(elevatorMovingLED, HIGH);
  digitalWrite(floor0LED, HIGH);     // Inițializare stare curentă
}

void loop() {
  // Verificare butoane apăsate
  if (digitalRead(floor0ButtonPin) == LOW) {
    moveElevator(0);
  } else if (digitalRead(floor1ButtonPin) == LOW) {
    moveElevator(1);
  } else if (digitalRead(floor2ButtonPin) == LOW) {
    moveElevator(2);
  }
  if (isMoving) {
    if (currentFloor == 0) {
      stopElevator();
    } else if (currentFloor == 1) {
      stopElevator();
    } else if (currentFloor == 2) {
      stopElevator();
    }
  }
  
}

void moveElevator(int targetFloor) {
  
  if (!isMoving) {
    isMoving = true;
    delay(2000);  
    // Stinge LED-urile 1 și 3
    digitalWrite(floor0LED, LOW);
    digitalWrite(floor2LED, LOW);
    if((currentFloor == 0 && targetFloor == 1) || (currentFloor == 1 && targetFloor == 2) || (currentFloor == 1 && targetFloor == 0) || (currentFloor == 2 && targetFloor == 1)){
      playFloorSound2();  // Redă sunetul la trecerea prin etaj
      digitalWrite(elevatorMovingLED, LOW); 
      delay(500); 
      digitalWrite(elevatorMovingLED, HIGH);
      delay(500); 
    }
    else{
      if ((currentFloor == 0 && targetFloor == 2) || (currentFloor == 2 and targetFloor == 0)) {
      playFloorSound1();  // Redă sunetul la trecerea prin etaj
      digitalWrite(elevatorMovingLED, LOW); 
      delay(500);
      digitalWrite(elevatorMovingLED, HIGH);
      delay(500); 
      digitalWrite(elevatorMovingLED, LOW);
      delay(500); 
      digitalWrite(elevatorMovingLED, HIGH);
      delay(500);
      digitalWrite(floor1LED, HIGH);
      digitalWrite(elevatorMovingLED, LOW); 
      delay(500); 
      digitalWrite(elevatorMovingLED, HIGH);
      delay(500); 
      digitalWrite(elevatorMovingLED, LOW); 
      delay(500); 
      digitalWrite(elevatorMovingLED, HIGH);
      delay(500);
        digitalWrite(floor1LED, LOW);
      }
    }
    // Actualizează etajul curent și LED-urile etajelor
    currentFloor = targetFloor;
    updateFloorLEDs();
    stopElevator();  // Oprește liftul după sosirea la destinație
  }
   playFloorSound();  // Redă sunetul la ajungerea liftului
}

void stopElevator() {
  isMoving = false;
  digitalWrite(elevatorMovingLED, HIGH);
  delay(1000);  
  updateFloorLEDs();
}

void updateFloorLEDs() {
  digitalWrite(floor0LED, LOW);
  digitalWrite(floor1LED, LOW);
  digitalWrite(floor2LED, LOW);
  if (currentFloor == 0) {
    digitalWrite(floor0LED, HIGH);
  } else if (currentFloor == 1) {
    digitalWrite(floor1LED, HIGH);
  } else if (currentFloor == 2) {
    digitalWrite(floor2LED, HIGH);
  }
}
void playFloorSound() {
  tone(buzzerPin, 1000, 200);  // Generează un sunet de 1000 Hz pentru 200 de milisecunde
}
void playFloorSound1()
{
  tone(buzzerPin, 500, 4000);  // Generează un sunet de 500 Hz pentru 4000 de milisecunde
}
void playFloorSound2()
{
  tone(buzzerPin, 500, 1000);  // Generează un sunet de 1000 Hz pentru 1000 de milisecunde
}
