#include "midi.h"


void midiCCsend(uint8_t channel, uint8_t cmd, uint8_t value) {
  Serial.write(0xb0);
  Serial.write(cmd);
  Serial.write(value);
}

