#ifndef LED_H
#define LED_H

#include <Arduino.h>

// Pin definitions
#define LED0 3
#define LED1 5
#define LED2 6
#define LED3 9
#define LED4 10
#define LED5 11
// Other macros
#define DEFAULT_BRIGHTNESS 30

// Led class definition
class Led {
private:
  uint8_t pin;
  bool status;
  uint8_t brightness;
  unsigned long startTime;
  unsigned long duration;
  bool isTiming;

public:
  // Constructor
  Led(uint8_t pin, uint8_t brightness = DEFAULT_BRIGHTNESS);

  // Getters / setters
  bool getStatus();

  // Methods
  void turnOn();
  void turnOff();
  void turnTo(bool status);
  void toggle();
  void setBrightness(uint8_t newBrightness);
  void lightFor(unsigned long duration);
  void update();
};

#endif
