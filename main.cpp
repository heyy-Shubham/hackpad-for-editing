#include <Arduino.h>
#include <Keyboard.h>

#define SW1  2
#define SW2  3
#define SW3  4
#define SW4  5
#define SW5  6
#define SW6  7
#define SW7  8
#define SW8  9
#define SW9  10
#define ENC_A 20
#define ENC_B 21

bool lastA = HIGH;
const int buttons[] = {SW1,SW2,SW3,SW4,SW5,SW6,SW7,SW8,SW9};
const int NUM_BUTTONS = 9;
bool lastState[9];
unsigned long lastPress[9];
#define DEBOUNCE 50

void pressKey(int sw) {
  switch (sw) {
    case 0: Keyboard.press(KEY_TAB); Keyboard.releaseAll(); break;
    case 1: Keyboard.press(KEY_LEFT_GUI); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('s'); Keyboard.releaseAll(); break;
    case 2: Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('z'); Keyboard.releaseAll(); break;
    case 3: Keyboard.press(KEY_LEFT_CTRL); Keyboard.press(KEY_LEFT_SHIFT); Keyboard.press('z'); Keyboard.releaseAll(); break;
    case 4: Keyboard.press(KEY_END); Keyboard.releaseAll(); break;
    case 5: Keyboard.press(KEY_LEFT_ALT); Keyboard.press('2'); Keyboard.releaseAll(); break;
    case 6: Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('b'); Keyboard.releaseAll(); break;
    case 7: Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('='); Keyboard.releaseAll(); break;
    case 8: Keyboard.press(KEY_LEFT_CTRL); Keyboard.press('-'); Keyboard.releaseAll(); break;
  }
}

void setup() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    pinMode(buttons[i], INPUT_PULLUP);
    lastState[i] = HIGH;
    lastPress[i] = 0;
  }
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  lastA = digitalRead(ENC_A);
  Keyboard.begin();
}

void loop() {
  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool state = digitalRead(buttons[i]);
    if (state == LOW && lastState[i] == HIGH) {
      if (millis() - lastPress[i] > DEBOUNCE) {
        pressKey(i);
        lastPress[i] = millis();
      }
    }
    lastState[i] = state;
  }
  bool currA = digitalRead(ENC_A);
  bool currB = digitalRead(ENC_B);
  if (currA != lastA) {
    if (currB != currA) { Keyboard.press(KEY_RIGHT_ARROW); Keyboard.releaseAll(); }
    else { Keyboard.press(KEY_LEFT_ARROW); Keyboard.releaseAll(); }
    lastA = currA;
  }
}
