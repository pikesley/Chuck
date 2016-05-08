#include "Arduino.h"
#include "Chuck.h"

Chuck::Chuck(int *pins, int pinCount, int sleep) {
  _pins = pins;
  _pinCount = pinCount;
  lights = pow(_pinCount, 2) - _pinCount;
  sleep = sleep;
  debugging = false;
}

void Chuck::debug(bool toggle) {
  Chuck::debugging = toggle;
  if (Chuck::debugging == true) {
    Serial.begin(9600);
  }
}

String Chuck::lightLed(int index) {
  int bracket = lights / _pinCount;
  int left = index / bracket;

  int candidates[_pinCount - 1];
  validateRhs(candidates, left);

  int right = candidates[index % (_pinCount - 1)];
  setPins(left, right);

  if (debugging) {
    String s = String(index);
    s = String(s + ": [ ");
    s = String(s + _pins[left]);
    s = String(s + ", ");
    s = String(s + _pins[right]);
    s = String(s + " ]");

    return s;
  }

  return("");
}

void Chuck::lightSeveral(int *list) {
  for (int t = 0; t < float(sleep) / (float(lights) * 2); t++) {
    for (int i = 0; i < lights; i++) {
      if (list[i] == 1) {
        Chuck::lightLed(i);
        delay(1);
      }
    }
  }
  resetPins();

}

void Chuck::wiring() {
  debug(true);
  Serial.begin(9600);
  for (int i = 0; i < lights; i++) {
    String s = String("For LED ");
    s = String(s + lightLed(i));
    Serial.println(s);
  }
  Serial.end();
}

void Chuck::resetPins() {
  Chuck::inputise();
  for (int i = 0; i < _pinCount; i++) {
    digitalWrite(_pins[i], LOW);
  }
}

// private

void Chuck::validateRhs(int *candidates, int left) {
  int bump = 0;

  for (int i = 0; i < _pinCount - 1; i++) {
    if (i == left) {
      bump = 1;
    }

    candidates[i] = i + bump;
  }
}

void Chuck::inputise() {
  for (int i = 0; i < _pinCount; i++) {
    pinMode(_pins[i], INPUT);
  }
}

void Chuck::setPins(int highIndex, int lowIndex) {
  resetPins();

  pinMode(_pins[highIndex], OUTPUT);
  pinMode(_pins[lowIndex], OUTPUT);

  digitalWrite(_pins[highIndex], HIGH);
  digitalWrite(_pins[lowIndex], LOW);
}
