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
bool toggleDouble = false;

//CC banks
uint8_t CCMap[6];  //the current mode cc codes
uint8_t CC1[6];
uint8_t CC2[6];
uint8_t CC3[6];
uint8_t CC4[6];
uint8_t CC5[6];
uint8_t CC6[6];

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

// nts3 stuff
uint8_t fx1Freeze = 0;
uint8_t fx2Freeze = 0;
uint8_t fx3Freeze = 0;
uint8_t fx4Freeze = 0;
uint8_t fx1Touch = 0;
uint8_t fx2Touch = 0;
uint8_t fx3Touch = 0;
uint8_t fx4Touch = 0;
uint8_t fx1 = 0;
uint8_t fx2 = 0;
uint8_t fx3 = 0;
uint8_t fx4 = 0;

void setup() {
  delay(INIT_PAUSE_MS);
  Serial.begin(MIDI_BAUD_RATE);
  initSequence(leds);
  selectPreset(CC1, CC2, CC3, CC4, CC5, CC6);
  mode = MODE_CC1;
  channel = START_CHANNEL;
  mapCC(CCMap, CC1);

  midiCCsend(0, CC1[0], 0);
  midiCCsend(0, CC1[1], 1);
  midiCCsend(0, CC1[2], 2);
  midiCCsend(0, CC1[3], 3);
  midiCCsend(0, CC1[4], 4);
  midiCCsend(0, CC1[5], 5);

  midiCCsend(0, CCMap[0], 0);
  midiCCsend(0, CCMap[1], 1);
  midiCCsend(0, CCMap[2], 2);
  midiCCsend(0, CCMap[3], 3);
  midiCCsend(0, CCMap[4], 4);
  midiCCsend(0, CCMap[5], 5);
}

void loop() {
  bool doublePressMode = false;
  // double switch presses
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

  // 1+5 FX1 touch toggle
  if (button0.isPressed() && button4.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx1Touch ^= 1;
      midiCCsend(channel, CC_FX1_TOUCH, 127 * fx1Touch);
    }
  }
  // 2+5 FX2 touch toggle
  if (button1.isPressed() && button4.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx2Touch ^= 1;
      midiCCsend(channel, CC_FX2_TOUCH, 127 * fx2Touch);
    }
  }
  // 3+5 FX3 touch toggle
  if (button2.isPressed() && button4.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx3Touch ^= 1;
      midiCCsend(channel, CC_FX3_TOUCH, 127 * fx3Touch);
    }
  }
  // 4+5 FX4 touch toggle
  if (button3.isPressed() && button4.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx4Touch ^= 1;
      midiCCsend(channel, CC_FX4_TOUCH, 127 * fx4Touch);
    }
  }

    // 1+5 FX1 touch toggle
  if (button0.isPressed() && button5.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx1 ^= 1;
      midiCCsend(channel, CC_FX1_ENABLE, 127 * fx1);
    }
  }
  // 2+5 FX2 touch toggle
  if (button1.isPressed() && button5.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx2 ^= 1;
      midiCCsend(channel, CC_FX2_ENABLE, 127 * fx2);
    }
  }
  // 3+5 FX3 touch toggle
  if (button2.isPressed() && button5.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx3 ^= 1;
      midiCCsend(channel, CC_FX3_ENABLE, 127 * fx3);
    }
  }
  // 4+5 FX4 touch toggle
  if (button3.isPressed() && button5.isPressed()) {
    doublePressMode = true;
    if (toggleDouble == false){
      toggleDouble = true;
      fx4 ^= 1;
      midiCCsend(channel, CC_FX4_ENABLE, 127 * fx4);
    }
  }

  if (!doublePressMode) {
    toggleDouble = false;
    // single switch presses
    if (button0.wasJustPressed()) {
      if (mode != MODE_CC1){
        mode = MODE_CC1;
        mapCC(CCMap, CC1);
      }else{
        fx1Freeze ^= 1;
        midiCCsend(channel, CC_FX1_FREEZE, 127 * fx1Freeze);
      }
    } else if (button1.wasJustPressed()) {
      if (mode != MODE_CC2){
        mode = MODE_CC2;
        mapCC(CCMap, CC2);
      }else{
        fx2Freeze ^= 1;
        midiCCsend(channel, CC_FX2_FREEZE, 127 * fx2Freeze);
      }
    } else if (button2.wasJustPressed()) {
      if (mode != MODE_CC3){
        mode = MODE_CC3;
        mapCC(CCMap, CC3);
      }else{
        fx3Freeze ^= 1;
        midiCCsend(channel, CC_FX3_FREEZE, 127 * fx3Freeze);
      }
    } else if (button3.wasJustPressed()) {
      if (mode != MODE_CC4){
        mode = MODE_CC4;
        mapCC(CCMap, CC4);
      }else{
        fx4Freeze ^= 1;
        midiCCsend(channel, CC_FX4_FREEZE, 127 * fx4Freeze);
      }
    } else if (button4.wasJustPressed()) {
      if (mode != MODE_CC5){
        mode = MODE_CC5;
        mapCC(CCMap, CC5);
      }
    } else if (button5.wasJustPressed()) {
      if (mode != MODE_CC6){
        mode = MODE_CC6;
        mapCC(CCMap, CC6);
      }
    }

    // pots
    uint8_t avgValues[6];
    updateAllPots(pots, avgValues);

    // Send midi
    for (uint8_t i = 0; i < 6; i++) {
      if (pots[i].previousDifersCurrent()) {
        midiCCsend(channel, CCMap[i], getFinalValue(avgValues[i], logResponse, randomness, logness));
      }
    }

    // leds
    bool isFrozen = isCurrentPageFrozen(mode, fx1Freeze, fx2Freeze, fx3Freeze, fx4Freeze);
    ledUpdate(mode, leds, pots, setBrightness, isFrozen);
  }

  // wait
  delay(LOOP_PAUSE_MS);
}


bool isCurrentPageFrozen(uint8_t mode, uint8_t fx1f, uint8_t fx2f, uint8_t fx3f, uint8_t fx4f){
  if (mode == MODE_CC1 && fx1f == 1){
    return true;
  }
    if (mode == MODE_CC2 && fx2f == 1){
    return true;
  }
    if (mode == MODE_CC3 && fx3f == 1){
    return true;
  }
    if (mode == MODE_CC4 && fx4f == 1){
    return true;
  }
  return false;
}
