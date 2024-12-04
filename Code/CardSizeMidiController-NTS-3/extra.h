#include <stdint.h>
#ifndef EXTRA_H
#define EXTRA_H

#include <Arduino.h>
#include "Led.h"
#include "Potentiometer.h"
#include "PushButton.h"

#define MODE_CC1 0
#define MODE_CC2 1
#define MODE_CC3 2
#define MODE_CC4 3
#define MODE_CC5 4
#define MODE_CC6 5

#define START_CHANNEL 0

#define INIT_PAUSE_MS 100
#define LOOP_PAUSE_MS 5

extern uint8_t logResponse[128];

extern uint8_t nts3CC1[6];
extern uint8_t nts3CC2[6];
extern uint8_t nts3CC3[6];
extern uint8_t nts3CC4[6];
extern uint8_t nts3CC5[6];
extern uint8_t nts3CC6[6];

void initSequence(const Led* ledsInner);
void updateAllPots(Potentiometer* potsInner, uint8_t* avgValues);
void ledUpdate(const uint8_t mode, Led* ledsInner, const Potentiometer* potsInner, const uint8_t setBrightness, bool isFrozen);
void selectPreset(uint8_t* CC1Inner, uint8_t* CC2Inner, uint8_t* CC3Inner, uint8_t* CC4Inner, uint8_t* CC5Inner, uint8_t* CC6Inner);
void defaultBrightness(Led* ledsInner, const uint8_t except);
uint8_t getFinalValue(const uint8_t initialValue, const uint8_t* logValues, const int8_t randomness, const uint8_t logness);
uint8_t nextChannel(const uint8_t channel);
void ledMeter(Led * leds, const uint8_t meter, uint8_t brightness);
void mapCC(uint8_t* CCMap, const uint8_t *ccCode);
void copyCCMap(uint8_t* dest, const uint8_t* src);

#endif