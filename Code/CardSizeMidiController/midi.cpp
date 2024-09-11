#include "midi.h"




void midiCCsend(int channel, int cmd, int value) {
  Serial.write(0xb0 | channel);
  Serial.write(cmd);
  Serial.write(value);
}

