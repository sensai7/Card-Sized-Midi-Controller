#ifndef MIDI_H
#define MIDI_H

#include "Arduino.h"

// macros
#define MIDI_BAUD_RATE 31250
#define MIDI_CC_LEVEL 0X07
#define MIDI_CC_PAN 0X0A
#define MIDI_CC_WHEEL 0X01

#define CC_FX1_FREEZE 105
#define CC_FX2_FREEZE 109
#define CC_FX3_FREEZE 113
#define CC_FX4_FREEZE 117

#define CC_FX1_TOUCH 104
#define CC_FX2_TOUCH 108
#define CC_FX3_TOUCH 112
#define CC_FX4_TOUCH 116

#define CC_FX1_ENABLE 106
#define CC_FX2_ENABLE 110
#define CC_FX3_ENABLE 114
#define CC_FX4_ENABLE 118

// function prototypes
void midiCCsend(uint8_t channel, uint8_t cmd, uint8_t value);


#endif
