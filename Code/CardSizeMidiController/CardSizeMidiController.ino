#include <Arduino.h>
#include "midi.h"
#include "Led.h"
#include "PushButton.h"
#include "Potentiometer.h"
#include "extra.h"
#include <math.h>

// Global variables
uint8_t mode;
uint8_t channel;
int8_t randomness;
uint8_t logness;

//CC banks
uint8_t* CC1;
uint8_t* CC2;
uint8_t* CC3;

// Peripheral definitions
Led led0(LED0);
Led led1(LED1);
Led led2(LED2);
Led led3(LED3);
Led led4(LED4);
Led led5(LED5);
PushButton button0(BUTTON0);
PushButton button1(BUTTON1);
PushButton button2(BUTTON2);
PushButton button3(BUTTON3);
PushButton button4(BUTTON4);
PushButton button5(BUTTON5);
Potentiometer pot0(POT0);
Potentiometer pot1(POT1);
Potentiometer pot2(POT2);
Potentiometer pot3(POT3);
Potentiometer pot4(POT4);
Potentiometer pot5(POT5);
Led leds[6] = { led0, led1, led2, led3, led4, led5 };
PushButton buttons[6] = { button0, button1, button2, button3, button4, button5 };
Potentiometer pots[6] = { pot0, pot1, pot2, pot3, pot4, pot5 };

void setup() {
  delay(INIT_PAUSE_MS);
  Serial.begin(MIDI_BAUD_RATE);
  initSequence(leds);
  selectPreset(CC1, CC2, CC3, leds, buttons);
  mode = MODE_LEVEL;
  channel = START_CHANNEL;
}

void loop() {
  // todo double switch presses
	// 1+2 Randomness
	// if(!currentButtonState[0] && !currentButtonState[1]){
	// 	randomness = map(analogRead(potPort[5]), 0, 1023, 0, 127);
	// }
	// // 3+4 Logness
	// if(!currentButtonState[2] && !currentButtonState[3]){
	// 	logness = map(analogRead(potPort[5]), 0, 1023, 0, 255);
	// }



  // single switch presses
  if (button0.isPressed()) {
    mode = MODE_LEVEL;
  } else if (button1.isPressed()) {
    mode = MODE_PAN;
  } else if (button2.isPressed()) {
    mode = MODE_WHEEL;
  } else if (button3.isPressed()) {
    if (mode == MODE_CC1) {
      channel = nextChannel(channel);
    } else {
      mode = MODE_CC1;
    }
  } else if (button4.isPressed()) {
    if (mode == MODE_CC2) {
      channel = nextChannel(channel);
    } else {
      mode = MODE_CC2;
    }
  } else if (button5.isPressed()) {
    if (mode == MODE_CC3) {
      channel = nextChannel(channel);
    } else {
      mode = MODE_CC3;
    }
  }

  // pots
  uint8_t avgValues[6];
  updateAllPots(pots, avgValues);
  //todo change send thing depending on mode

  if (pot0.previousDifersCurrent()) {
    midiCCsend(0, 0x07, getFinalValue(avgValues[0], logResponse, randomness, logness));
    //todo test this
    //midiCCsend(0, 0x07, avgValues[0]);
  }
  if (pot1.previousDifersCurrent()) {
    midiCCsend(0, 0x07, avgValues[1]);
  }
  if (pot2.previousDifersCurrent()) {
    midiCCsend(0, 0x07, avgValues[2]);
  }
  if (pot3.previousDifersCurrent()) {
    midiCCsend(0, 0x07, avgValues[3]);
  }
  if (pot4.previousDifersCurrent()) {
    midiCCsend(0, 0x07, avgValues[4]);
  }
  if (pot5.previousDifersCurrent()) {
    midiCCsend(0, 0x07, avgValues[5]);
  }

  // leds
  ledUpdate(channel, mode, leds, pots);

  // wait
  delay(LOOP_PAUSE_MS);
}