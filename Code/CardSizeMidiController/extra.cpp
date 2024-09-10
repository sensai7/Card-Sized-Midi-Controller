#include <stdint.h>
#include "extra.h"


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


//Undefined CC
uint8_t undefinedCC1[] = { 2, 6, 13, 14, 15, 0x1F };
uint8_t undefinedCC2[] = { 7, 4, 5, 0x1F, 0x1F, 0x1F };
uint8_t undefinedCC3[] = { 0, 1, 3, 8, 9, 0x1F };

//preset CC
uint8_t volcaFMCC1[] = { 40, 41, 42, 43, 44, 45 };    //TRANSPOSE, VELOCITY, MODULATOR ATTACK, MODLULATOR DECAY, CARRIER ATTACK, CARRIER DECAY
uint8_t volcaFMCC2[] = { 46, 47, 48, 49, 50, 0x01 };  //LFO RATE, LFO PICTH DEPTH, ALGORITHM, ARP TYPE, ARP DIV
uint8_t volcaFMCC3[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

uint8_t volcaKeysCC1[] = { 5, 11, 40, 41, 42, 43 };       //PORTAMENTO, EXPRESSION, VOICE, OCTAVE, DETUNE, VCO EG INT
uint8_t volcaKeysCC2[] = { 44, 45, 46, 47, 48, 49 };      //CUTOFF, VCF EG INT, LFO RATE, LFO PITCH, LFO CUTOFF INT, EG ATTACK
uint8_t volcaKeysCC3[] = { 50, 51, 52, 53, 0x01, 0x01 };  //EG DECAY/RELEASE, EG SUSTAIN, DELAY TIME, DELAY FEEDBACK

uint8_t volcaBassCC1[] = { 5, 11, 40, 41, 42, 43 };   //SLIDE TIME, EXPRESSION, OCTAVE, LFO RATE, LFO INT, VCO PITCH 1
uint8_t volcaBassCC2[] = { 44, 45, 46, 47, 48, 49 };  //VCO PITCH 2, VCO PITCH 3, EG ATTACK, EG DECAY/RELEASE, CUTOFF EG INT, GATE TIME
uint8_t volcaBassCC3[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

uint8_t volcaNubassCC1[] = { 40, 41, 42, 43, 44, 45 };    //VTO PITCH, VTO SATURATION, VTO LEVEL, VCF CUTOFF, VCF PEAK, VCF ATTACK
uint8_t volcaNubassCC2[] = { 46, 47, 48, 49, 50, 0x01 };  //VCF DECAY, VCF EG INT, ACCENT, LFO RATE, LFO INT
uint8_t volcaNubassCC3[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

uint8_t volcaKickCC1[] = { 40, 41, 42, 43, 44, 45 };      //PULSE COLOUR, PULSE LEVEL, AMP ATTACK, AMP DECAY, DRIVE, TONE
uint8_t volcaKickCC2[] = { 46, 47, 48, 49, 0x01, 0x01 };  //RESONATOR PITCH, RESONATOR BEND, RESONATOR TIME, ACCENT
uint8_t volcaKickCC3[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };

uint8_t volcaSampleCC1[] = { 40, 41, 42, 43, 44, 45 };        //SAMPLE START POINT, SAMPLE LENGTH, HI CUT, SPEED, PITCH EG INT, PITCH EG ATTACK
uint8_t volcaSampleCC2[] = { 46, 47, 48, 0x01, 0x01, 0x01 };  //PITCH EG DECAY, AMP EG ATTACK, AMP EG DECAY
uint8_t volcaSampleCC3[] = { 0x01, 0x01, 0x01, 0x01, 0x01, 0x01 };


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

void ledUpdate(const uint8_t channel, const uint8_t mode, Led* ledsInner, const Potentiometer* potsInner) {
  if (mode <= MODE_WHEEL) {  //modes level/pan/wheel -> lit all leds, brightness to pot position
    for (uint8_t i = 0; i < 6; i++) {
      ledsInner[i].turnOn();
      ledsInner[i].setBrightness(potsInner[i].getCurrentAverage());
    }
  } else {  //CC Modes -> lit the current channel led
    for (uint8_t i = 0; i < 6; i++) {
      (i == channel || i == mode) ? ledsInner[i].turnOn() : ledsInner[i].turnOff();
      if (i == mode) {
        ledsInner[i].setBrightness(1);
      }
      if (i == channel) {
        ledsInner[i].setBrightness(DEFAULT_BRIGHTNESS);
      }
    }
  }
}


void selectPreset(uint8_t* CC1Inner, uint8_t* CC2Inner, uint8_t* CC3Inner, Led* ledsInner, PushButton* buttonsInner) {
  int8_t preset = -1;
  for (int8_t i = 0; i < 6; i++) {
    if (!buttonsInner[i].instantRead()) {
      preset = i;
      break;
    }
  }
  switch (preset) {
    case 0:
      CC1Inner = volcaFMCC1;
      CC2Inner = volcaFMCC2;
      CC3Inner = volcaFMCC3;
      break;
    case 1:
      CC1Inner = volcaKeysCC1;
      CC2Inner = volcaKeysCC2;
      CC3Inner = volcaKeysCC3;
      break;
    case 2:
      CC1Inner = volcaBassCC1;
      CC2Inner = volcaBassCC2;
      CC3Inner = volcaBassCC3;
      break;
    case 3:
      CC1Inner = volcaNubassCC1;
      CC2Inner = volcaNubassCC2;
      CC3Inner = volcaNubassCC3;
      break;
    case 4:
      CC1Inner = volcaKickCC1;
      CC2Inner = volcaKickCC2;
      CC3Inner = volcaKickCC3;
      break;
    case 5:
      CC1Inner = volcaSampleCC1;
      CC2Inner = volcaSampleCC2;
      CC3Inner = volcaSampleCC3;
      break;
    default:
      CC1Inner = undefinedCC1;
      CC2Inner = undefinedCC2;
      CC3Inner = undefinedCC3;
      break;
  }
  if (preset >= 0) {
    ledsInner[preset].turnOn();
    delay(INIT_PAUSE_MS * 6);
    ledsInner[preset].turnOff();
  }
}

uint8_t getFinalValue(const uint8_t initialValue, const uint8_t* logValues, const int8_t randomness, const uint8_t logness) {
  uint8_t finalValue;
  uint8_t variation = random(-randomness, randomness);
  finalValue = (initialValue * (255 - logness)) / 255 + (logValues[initialValue] * logness) / 255 + variation;
  return finalValue;
}

uint8_t nextChannel(const uint8_t channel){
  return (channel + 1) % 6;
}