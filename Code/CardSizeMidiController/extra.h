#include <stdint.h>
#ifndef EXTRA_H
#define EXTRA_H

#include <Arduino.h>
#include "Led.h"
#include "Potentiometer.h"
#include "PushButton.h"

#define MODE_LEVEL 0
#define MODE_PAN 1
#define MODE_WHEEL 2
#define MODE_CC1 3
#define MODE_CC2 4
#define MODE_CC3 5
#define START_CHANNEL 0

#define INIT_PAUSE_MS 100
#define LOOP_PAUSE_MS 5

extern uint8_t logResponse[128];

extern uint8_t undefinedCC1[];
extern uint8_t undefinedCC2[];
extern uint8_t undefinedCC3[];

extern uint8_t volcaFMCC1[];
extern uint8_t volcaFMCC2[];
extern uint8_t volcaFMCC3[];

extern uint8_t volcaKeysCC1[];
extern uint8_t volcaKeysCC2[];
extern uint8_t volcaKeysCC3[];

extern uint8_t volcaKeysCC1[];
extern uint8_t volcaKeysCC2[];
extern uint8_t volcaKeysCC3[];

extern uint8_t volcaBassCC1[];
extern uint8_t volcaBassCC2[];
extern uint8_t volcaBassCC3[];

extern uint8_t volcaNubassCC1[];
extern uint8_t volcaNubassCC2[];
extern uint8_t volcaNubassCC3[];

extern uint8_t volcaKickCC1[];
extern uint8_t volcaKickCC2[];
extern uint8_t volcaKickCC3[];

extern uint8_t volcaSampleCC1[];
extern uint8_t volcaSampleCC2[];
extern uint8_t volcaSampleCC3[];

void initSequence(const Led* ledsInner);
void updateAllPots(Potentiometer* potsInner, uint8_t* avgValues);
void ledUpdate(const uint8_t channel, const uint8_t mode, Led* ledsInner, const Potentiometer* potsInner);
void selectPreset(uint8_t* CC1Inner, uint8_t* CC2Inner, uint8_t* CC3Inner, Led* ledsInner, PushButton * buttonsInner);
void defaultBrightness(Led* ledsInner, const uint8_t except);
uint8_t getFinalValue(const uint8_t initialValue, const uint8_t* logValues, const int8_t randomness, const uint8_t logness);
uint8_t nextChannel(const uint8_t channel);

#endif