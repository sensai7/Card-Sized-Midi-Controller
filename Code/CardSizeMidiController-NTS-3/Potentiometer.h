#include <stdint.h>
#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

// Pin definitions
#define POT0 A0
#define POT1 A3
#define POT2 A1
#define POT3 A4
#define POT4 A2
#define POT5 A5
// Other macros
#define SAMPLING 11  //samples for the averaging

// function protytypes
int median(uint8_t *a, int n);
void swap(uint8_t *p, uint8_t *q);

class Potentiometer {
private:
  uint8_t pin;                 // Analog pin connected to the potentiometer
  uint8_t index;               // Index for the current position in the readings array
  uint8_t readings[SAMPLING];  // Array to store readings for averaging
  uint8_t currentAveraged;     // Current averaged value
  uint8_t previousAveraged;    // Previous averaged value
  uint8_t previousReading;

public:
  Potentiometer(uint8_t pin);  // Constructor
  int readRaw();               // Read and map the potentiometer value
  void update();               // Read and update the average
  uint8_t getCurrentAverage(); // Get the averaged value
  bool previousDifersCurrent();// Returns true if currentAveraged is different than previousAveraged
};

#endif