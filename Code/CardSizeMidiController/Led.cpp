#include "Led.h"

// Constructor
Led::Led(uint8_t pin, uint8_t brightness = DEFAULT_BRIGHTNESS) {
  this->pin = pin;
  this->brightness = brightness;
  this->status = 0;
  analogWrite(pin, 0);
}

// Getter method to return the status of the LED
bool Led::getStatus() {
  return status;
}

// Method to turn the LED on
void Led::turnOn() {
  status = 1;
  analogWrite(pin, brightness);
}

// Method to turn the LED off
void Led::turnOff() {
  status = 0;
  analogWrite(pin, 0);
}

// Method to turn the LED to the desired status
void Led::turnTo(bool status) {
  analogWrite(pin, brightness * status);
}

// Method to toggle the LED state
void Led::toggle() {
  if (status == 0) {
    turnOn();
  } else {
    turnOff();
  }
}

// Method to set the brightness of the LED
void Led::setBrightness(uint8_t newBrightness) {
  brightness = newBrightness;
  if (status == 1) {  // If the LED is currently on, update the brightness immediately
    analogWrite(pin, brightness);
  }
}

// Method to turn on the LED for a specific duration (non-blocking)
void Led::lightFor(unsigned long duration) {
  this->duration = duration;
  this->startTime = millis();
  this->isTiming = true;
  turnOn();  // Turn on the LED
}

// Method to manage timed operations (should be called frequently, e.g., in loop)
void Led::update() {
  if (isTiming && (millis() - startTime >= duration)) {
    turnOff();         // Turn off the LED after the duration has passed
    isTiming = false;  // Reset the timing flag
  }
}
