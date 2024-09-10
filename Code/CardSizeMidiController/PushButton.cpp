#include "PushButton.h"

// Constructor
PushButton::PushButton(uint8_t pin) {
  this->pin = pin;
  this->buttonState = HIGH;
  this->lastButtonState = HIGH;
  pinMode(pin, INPUT_PULLUP);
}

bool PushButton::instantRead(){
  lastButtonState = buttonState;
  buttonState = digitalRead(pin);
  return buttonState;
}

bool PushButton::isPressed() {
  return (instantRead() == LOW && lastButtonState == HIGH);
}

bool PushButton::isReleased() {
  return (instantRead() == HIGH && lastButtonState == LOW);
}

