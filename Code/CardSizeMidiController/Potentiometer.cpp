#include "Potentiometer.h"

// Constructor
Potentiometer::Potentiometer(uint8_t pin) {
  this->pin = pin;
  this->index = 0;
  this->currentAveraged = 0;
  this->previousAveraged = 0;
  for (int i = 0; i < SAMPLING; i++) {
    readings[i] = 0;
  }
}

// Read the current value from the potentiometer, map it, and update the readings
int Potentiometer::readRaw() {
  return analogRead(pin);
}

void Potentiometer::update() {
  uint16_t rawValue = readRaw();                         // Read the raw analog value (0-1023)
  uint8_t mappedValue = map(rawValue, 0, 1023, 0, 127);  // Map to 7 bit 0-127
  readings[index] = mappedValue;                         // Store the reading in the array

  index = (index + 1) % SAMPLING;
  previousAveraged = currentAveraged;
  currentAveraged = median(readings, SAMPLING);
}

// void Potentiometer::update() {
//   uint16_t rawValue = readRaw();                         // Read the raw analog value (0-1023)
//   uint8_t mappedValue = map(rawValue, 0, 1023, 0, 127);  // Map to 7-bit (0-127)

//   if (abs(mappedValue - previousReading) >= 2) {
//     readings[index] = mappedValue;
//     index = (index + 1) % SAMPLING;
//     previousReading = mappedValue;

//     previousAveraged = currentAveraged;
//     currentAveraged = median(readings, SAMPLING);
//   }
// }
  

  // Get the averaged value of the potentiometer readings
  uint8_t Potentiometer::getCurrentAverage() {
    return currentAveraged;
  }

  bool Potentiometer::previousDifersCurrent() {
    return currentAveraged != previousAveraged;
  }


  int median(uint8_t * a, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
      for (j = 0; j < n - i - 1; j++) {
        if (a[j] > a[j + 1])
          swap(&a[j], &a[j + 1]);
      }
    }
    n = (n + 1) / 2 - 1;
    return a[n];
  }

  void swap(uint8_t * p, uint8_t * q) {
    int t;
    t = *p;
    *p = *q;
    *q = t;
  }
