#ifndef MIDI_H
#define MIDI_H

#include "Arduino.h"

// macros
#define MIDI_BAUD_RATE 31250

// function prototypes
void midiCCsend(int channel, int cmd, int value);


#endif
