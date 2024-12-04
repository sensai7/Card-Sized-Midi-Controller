#include <stdint.h>
#include "extra.h"
#include "midi.h"


uint8_t logResponse[128] = { 0, 18, 29, 37, 42, 47, 51, 55, 58, 61, 63, 66, 68, 70, 71,
                             73, 75, 76, 78, 79, 80, 82, 83, 84, 85, 86, 87, 88, 89, 90,
                             91, 91, 92, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100,
                             100, 101, 102, 102, 103, 103, 104, 104, 105, 105, 106, 106,
                             107, 107, 108, 108, 108, 109, 109, 110, 110, 111, 111, 111,
                             112, 112, 112, 113, 113, 114, 114, 114, 115, 115, 115, 116,
                             116, 116, 117, 117, 117, 118, 118, 118, 118, 119, 119, 119,
                             120, 120, 120, 120, 121, 121, 121, 121, 122, 122, 122, 123,
                             123, 123, 123, 124, 124, 124, 124, 124, 125, 125, 125, 125,
                             126, 126, 126, 126, 127, 127, 127, 127, 127, 128, 128, 128 };


uint8_t nts3CC1[6] = {16, 48, 17, 49, 18, 50};
uint8_t nts3CC2[6] = {20, 52, 21, 53, 22, 54};
uint8_t nts3CC3[6] = {24, 56, 25, 57, 26, 58};
uint8_t nts3CC4[6] = {28, 60, 29, 61, 30, 62};
uint8_t nts3CC5[6] = {12, 44, 13, 45, 14, 46};
uint8_t nts3CC6[6] = {7, 39, 80, 81, 82, 83};


void initSequence(const Led* ledsInner) {
  ledsInner[0].turnOn();
  ledsInner[5].turnOn();
  delay(80);
  ledsInner[0].turnOff();
  ledsInner[5].turnOff();
  ledsInner[1].turnOn();
  ledsInner[4].turnOn();
  delay(80);
  ledsInner[1].turnOff();
  ledsInner[4].turnOff();
  ledsInner[2].turnOn();
  ledsInner[3].turnOn();
  delay(80);
  ledsInner[2].turnOff();
  ledsInner[3].turnOff();
  ledsInner[0].turnOn();
  ledsInner[5].turnOn();
  delay(50);
  ledsInner[0].turnOff();
  ledsInner[5].turnOff();
  ledsInner[1].turnOn();
  ledsInner[4].turnOn();
  delay(50);
  ledsInner[1].turnOff();
  ledsInner[4].turnOff();
  ledsInner[2].turnOn();
  ledsInner[3].turnOn();
  delay(50);
  ledsInner[2].turnOff();
  ledsInner[3].turnOff();
}

void updateAllPots(Potentiometer* potsInner, uint8_t* avgValues) {
  potsInner[0].update();
  potsInner[1].update();
  potsInner[2].update();
  potsInner[3].update();
  potsInner[4].update();
  potsInner[5].update();
  avgValues[0] = potsInner[0].getCurrentAverage();
  avgValues[1] = potsInner[1].getCurrentAverage();
  avgValues[2] = potsInner[2].getCurrentAverage();
  avgValues[3] = potsInner[3].getCurrentAverage();
  avgValues[4] = potsInner[4].getCurrentAverage();
  avgValues[5] = potsInner[5].getCurrentAverage();
}

void ledUpdate(const uint8_t mode, Led* ledsInner, const Potentiometer* potsInner, const uint8_t setBrightness, bool isFrozen) {
  // if (mode <= MODE_WHEEL) {  //modes level/pan/wheel -> lit all leds, brightness to pot position
  //   for (uint8_t i = 0; i < 6; i++) {
  //     ledsInner[i].turnOn();
  //     ledsInner[i].setBrightness(potsInner[i].getCurrentAverage());
  //   }
  // } else {  //CC Modes -> lit the current channel led
    for (uint8_t i = 0; i < 6; i++) {
      if (i == mode){
        if (isFrozen){
          ledsInner[i].setBrightness(1);
        }else{
          ledsInner[i].setBrightness(setBrightness);
        }
        ledsInner[i].turnOn();
      }else{
        ledsInner[i].turnOff();
      }
    }
  // }
}


void selectPreset(uint8_t* CC1Inner, uint8_t* CC2Inner, uint8_t* CC3Inner, uint8_t* CC4Inner, uint8_t* CC5Inner, uint8_t* CC6Inner) {
  copyCCMap(CC1Inner, nts3CC1);
  copyCCMap(CC2Inner, nts3CC2);
  copyCCMap(CC3Inner, nts3CC3);
  copyCCMap(CC4Inner, nts3CC4);
  copyCCMap(CC5Inner, nts3CC5);
  copyCCMap(CC6Inner, nts3CC6);
}

uint8_t getFinalValue(const uint8_t initialValue, const uint8_t* logValues, const int8_t randomness, const uint8_t logness) {
  int16_t finalValue;
  int8_t variation = random(-randomness, randomness);
  finalValue = (initialValue * (255 - logness)) / 255 + (logValues[initialValue] * logness) / 255 + variation;
  if (finalValue < 0) finalValue = 0;
  if (finalValue > 127) finalValue = 127;
  return finalValue;
}

uint8_t nextChannel(const uint8_t channel) {
  return (channel + 1) % 6;
}

void ledMeter(Led* leds, const uint8_t meter, uint8_t brightness) {
  uint8_t nLitLeds = map(meter, 0, 127, 0, 5);
  for (uint8_t i = 0; i < 6; i++) {
    if (i <= nLitLeds) {
      leds[i].turnOn();
      leds[i].setBrightness(brightness);
    } else {
      leds[i].turnOff();
    }
  }
}

void mapCC(uint8_t* CCMap, const uint8_t *ccCode) {
  for (uint8_t i = 0; i < 6; i++) CCMap[i] = ccCode[i];
}

void copyCCMap(uint8_t* dest, const uint8_t* src) {
  for (uint8_t i = 0; i < 6; i++) {
    dest[i] = src[i];
  }
}