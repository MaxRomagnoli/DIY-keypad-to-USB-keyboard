#include "Keyboard.h"
#include "Keypad.h"

#define ROWS   4
#define COLS   3
#define buzzer A3

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {3, 4, 5, 6};
byte colPins[COLS] = {7, 8, 9};

unsigned long lastPeriodStart;

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.println(customKey);

    //Keyboard
    if (customKey == '#') {
      Keyboard.write(176); //ENTER
    } else if (customKey == '*') {
      Keyboard.write(177); //ESC
    } else {
      Keyboard.print(customKey); //0-9
    }

    //Buzzer
    tone(buzzer, random(200, 600));
    lastPeriodStart = millis() + 100; //set timer 100ms for stopping the buzzer
  } else if (millis() > lastPeriodStart) {
    noTone(buzzer); //stop the buzzer
  }
}
