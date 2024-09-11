#include <Arduino.h>
#include "midi.h"
#include "Led.h"
#include "PushButton.h"
#include "Potentiometer.h"
#include "extra.h"

// Global variables
uint8_t mode;
uint8_t channel;
int8_t randomness;
uint8_t logness;
uint8_t setBrightness = DEFAULT_BRIGHTNESS;

//CC banks
uint8_t CCMap[6];  //the current mode cc codes
uint8_t CC1[6];
uint8_t CC2[6];
uint8_t CC3[6];

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
  mapCC(CCMap, MIDI_CC_LEVEL);
}

void loop() {
  // double switch presses
  bool doublePressMode = false;
  // 1+2 Randomness
  if (button0.isPressed() && button1.isPressed()) {
    doublePressMode = true;
    pot5.update();
    randomness = pot5.getCurrentAverage();
    ledMeter(leds, randomness, setBrightness);
  }
  // 3+4 Logness
  if (button2.isPressed() && button3.isPressed()) {
    doublePressMode = true;
    pot5.update();
    logness = pot5.getCurrentAverage();
    ledMeter(leds, logness, setBrightness);
  }
  // 5+6 set brightness
  if (button4.isPressed() && button5.isPressed()) {
    doublePressMode = true;
    pot5.update();
    setBrightness = pot5.getCurrentAverage();
    if (setBrightness == 0) setBrightness = 1;
    ledMeter(leds, setBrightness, setBrightness);
  }


  if (!doublePressMode) {
    // single switch presses
    if (button0.wasJustPressed()) {
      mode = MODE_LEVEL;
      mapCC(CCMap, MIDI_CC_LEVEL);
    } else if (button1.wasJustPressed()) {
      mode = MODE_PAN;
      mapCC(CCMap, MIDI_CC_PAN);
    } else if (button2.wasJustPressed()) {
      mode = MODE_WHEEL;
      mapCC(CCMap, MIDI_CC_WHEEL);
    } else if (button3.wasJustPressed()) {
      if (mode == MODE_CC1) {
        channel = nextChannel(channel);
      } else {
        mode = MODE_CC1;
        copyCCMap(CCMap, CC1);
      }
    } else if (button4.wasJustPressed()) {
      if (mode == MODE_CC2) {
        channel = nextChannel(channel);
      } else {
        mode = MODE_CC2;
        copyCCMap(CCMap, CC2);
      }
    } else if (button5.wasJustPressed()) {
      if (mode == MODE_CC3) {
        channel = nextChannel(channel);
      } else {
        mode = MODE_CC3;
        copyCCMap(CCMap, CC3);
      }
    }

    // pots
    uint8_t avgValues[6];
    updateAllPots(pots, avgValues);

    // Send midi
    for (uint8_t i = 0; i < 6; i++) {
      if (pots[i].previousDifersCurrent()) {
        uint8_t targetChannel = (mode <= MODE_WHEEL) ? i : channel;
        midiCCsend(targetChannel, CCMap[i], getFinalValue(avgValues[i], logResponse, randomness, logness));
      }
    }

    // leds
    ledUpdate(channel, mode, leds, pots, setBrightness);
  }

  // wait
  delay(LOOP_PAUSE_MS);
}