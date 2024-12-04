#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include "Arduino.h"

// Pin definitions
#define BUTTON0 2
#define BUTTON1 8
#define BUTTON2 4
#define BUTTON3 12
#define BUTTON4 7
#define BUTTON5 13
// Other macros
#define DEFAULT_BOUNCING 50

class PushButton {
private:
  uint8_t pin;                     // Pin where the button is connected
  bool buttonState;                // Current state of the button
  bool lastButtonState;            // Last stable state of the button

public:
  PushButton(uint8_t pin);
  bool wasJustPressed();    // Check if the button was pressed right now
  bool wasJustReleased();
  bool isPressed();
  bool isReleased();   // Check if the button is released
  bool instantRead();  // No debounce
  bool read();         // Read the current state of the button with debounce

};

#endif
