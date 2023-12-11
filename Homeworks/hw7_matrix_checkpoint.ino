#include "LedControl.h"
#include <LiquidCrystal.h>

const byte rs = 9;
const byte en = 8;
const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;
const int xPin = A0;
const int yPin = A1;
const int buttonPin = 13;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

byte matrixBrightness = 2;
byte xPos = 7;
byte yPos = 5;
byte xLastPos = 0;
byte yLastPos = 0;

const int minThreshold = 312;
const int maxThreshold = 712;
const byte moveInterval = 200;
unsigned long long lastMoved = 0;

const int blinkIntervalPlayer = 1000;
unsigned long long lastBlinkPlayer = 0;

const int bombDelay = 3000;
unsigned long long bombPlacementTime = 0;

const byte matrixSize = 8;
bool matrixChanged = true;

const byte PLAYER = 1;
const byte WALL = 2;
const byte BOMB = 3;
const byte EXPLOSION_SIZE = 1;

byte matrix[matrixSize][matrixSize] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

enum MenuOption {
  START_GAME,
  SETTINGS,
  ABOUT
};

MenuOption currentMenuOption = START_GAME;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Welcome to the");   // scriem mesajul de inceput
  lcd.setCursor(0, 1);
  lcd.print("Matrix Game!");
  delay(5000);
  lcd.clear();
  showMenu();

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  // plaseaza peretii aleatoriu, evitand pozitia initiala a jucatorului
  for (int i = 0; i < matrixSize * matrixSize / 2; i++) {
    int wallX, wallY;
    do {
      wallX = random(matrixSize);
      wallY = random(matrixSize);
    } while (wallX == xPos && wallY == yPos);
    matrix[wallX][wallY] = WALL;
  }
  matrix[xPos][yPos] = PLAYER;
  lastBlinkPlayer = 0;
}

void loop() {
  handleMenuInput();
  
  /*if (digitalRead(buttonPin) == HIGH) {
    handleMenuSelection();
  }
*/
  if (currentMenuOption == START_GAME) {
    if (millis() - lastMoved > moveInterval) {
      updatePositions();
      lastMoved = millis();
    }
    if (digitalRead(buttonPin) == HIGH) {
      if (matrix[xPos][yPos] == WALL) {
        placeBomb();    // se plaseaza bomba 
      }
    }

    if (millis() - bombPlacementTime > bombDelay) {
      explodeBombs();  // explodeaza bomba
    }
    // verifica conditia de castig (toti peretii sunt distrusi)
    bool allWallsDestroyed = true;
    for (int i = 0; i < matrixSize; i++) {
      for (int j = 0; j < matrixSize; j++) {
        if (matrix[i][j] == WALL) {
          allWallsDestroyed = false;
          break;
        }
      }
      if (!allWallsDestroyed) {
        break;
      }
    }

    if (allWallsDestroyed) {
      displaySmileFace();  // afiseaza fata zambitoare
    }

    if (millis() - lastBlinkPlayer > blinkIntervalPlayer) {
      matrixChanged = true;
      lastBlinkPlayer = millis();
    }
    if (matrixChanged == true) {
      updateMatrix();
      matrixChanged = false;
    }
  }
}

void handleMenuInput() {
  int joystickXValue = analogRead(xPin);

  const int newMinThreshold = 400;
  const int newMaxThreshold = 600;

  if (joystickXValue < newMinThreshold) {
    changeMenuOption(-1);
  } else if (joystickXValue > newMaxThreshold) {
    changeMenuOption(1);
  }
}

void changeMenuOption(int direction) {
  int numMenuOptions = 3;
  currentMenuOption = static_cast<MenuOption>((currentMenuOption + direction + numMenuOptions) % numMenuOptions);
  showMenu();
}

void showMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Menu:");

  lcd.setCursor(0, 1);
  switch (currentMenuOption) {
    case START_GAME:
      lcd.print("> Start Game");
      break;
    case SETTINGS:
      lcd.print("> Settings");
      break;
    case ABOUT:
      lcd.print("> About");
      break;
  }
}

void handleMenuSelection() {
  switch (currentMenuOption) {
    case START_GAME:
      lcd.clear();
      lcd.print("Starting game...");
      delay(2000);
      lcd.clear();
      break;
    case SETTINGS:
      lcd.clear();
      lcd.print("Settings menu");
      delay(2000);
      lcd.clear();
      break;
    case ABOUT:
      lcd.clear();
      lcd.print("About this game");
      delay(2000);
      lcd.clear();
      break;
  }
}

void displaySmileFace() {
  // definirea matricei pentru fata zambitoare
  byte smileyFace[matrixSize][matrixSize] = {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 1, 1, 0, 0, 1, 1, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 0, 0, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0}
  };
  // afiseaza fata zambitoare pe matrice
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, smileyFace[row][col] * matrixBrightness);
    }
  }
}

void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      byte value = matrix[row][col];

      if (value == WALL || value == BOMB || value == PLAYER) {
        lc.setLed(0, row, col, matrixBrightness);
      } else {
        lc.setLed(0, row, col, 0);
      }
    }
  }
  if (matrix[xPos][yPos] == BOMB) {
    lc.setLed(0, xPos, yPos, matrixBrightness);
  }
}

void updatePositions() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  xLastPos = xPos;
  yLastPos = yPos;

  if (xValue < minThreshold) {
    movePlayer(1, 0);
  }
  if (xValue > maxThreshold) {
    movePlayer(-1, 0);
  }
  if (yValue > maxThreshold) {
    movePlayer(0, 1);
  }
  if (yValue < minThreshold) {
    movePlayer(0, -1);
  }
}

void movePlayer(int xChange, int yChange) {
  byte newPosX = constrain(xPos + xChange, 0, matrixSize - 1);
  byte newPosY = constrain(yPos + yChange, 0, matrixSize - 1);
  if (matrix[newPosX][newPosY] == 0) {
    matrixChanged = true;
    matrix[xPos][yPos] = 0;
    xPos = newPosX;
    yPos = newPosY;
    matrix[xPos][yPos] = PLAYER;
  }
}

void placeBomb() {
  if (matrix[xPos][yPos] == WALL) {
    matrix[xPos][yPos] = BOMB;
    bombPlacementTime = millis();
    matrixChanged = true;
  }
}

void explodeBombs() {
  bombPlacementTime = millis();
  for (int i = -EXPLOSION_SIZE; i <= EXPLOSION_SIZE; i++) {
    for (int j = -EXPLOSION_SIZE; j <= EXPLOSION_SIZE; j++) {
      int targetX = xPos + i;
      int targetY = yPos + j;

      if (targetX >= 0 && targetX < matrixSize && targetY >= 0 && targetY < matrixSize) {
        if (matrix[targetX][targetY] == WALL) {
          matrix[targetX][targetY] = 0;
        }
      }
    }
  }
  matrix[xPos][yPos] = 0;
  matrixChanged = true;
}
