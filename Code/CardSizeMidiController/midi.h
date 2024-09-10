#ifndef MIDI_H
#define MIDI_H

#include "Arduino.h"

// macros
#define MIDI_BAUD_RATE 31250
#define MIDI_CC_LEVEL 0X07
#define MIDI_CC_PAN 0X0A
#define MIDI_CC_WHEEL 0X01

// function prototypes
void midiCCsend(int channel, int cmd, int value);


#endif
