# Card Size Midi Controller
 Standard card sized MIDI controller, for level, pan, modulation wheel and control changes. Both hardware and software are open source, you can modify and use as you please.

![Board](https://i.imgur.com/5F0pWWH.png)

## Ordering your own board
This repository includes the necessary files to order your own board with the SMT components pre-soldered from JLCPCB's assembly service. To do so, follow this: 

 1. Go to their order page [LINK](https://cart.jlcpcb.com/quote) and upload the zipped gerber files. The default options should be fine, but you can customize your own board as you wish, the only thing I recommed changing is under "Remove Order Number" to "Specify a location"
 2. In the SMT Assembly select "Assemble top side", the quantity of boards (minimum is 2 as of today) and tooling holes added by JLCPCB.
 3. Add the BOM and CPL files when prompted and continue through the process.

## Adding the rest of components (BOM)

(!) each part links to the particular component in Tayda, but can be sourced from anywhere else. Aliexpress and eBay are worth looking for everything, but I'd suggest using tayda's metal potentiometers.

 * C1 10u [Tayda](https://www.taydaelectronics.com/capacitors/electrolytic-capacitors/10uf-16v-85c-radial-electrolytic-capacitor.html)
 * C2 100u [Tayda](https://www.taydaelectronics.com/capacitors/)electrolytic-capacitors/100uf-35v-105c-jrb-radial-electrolytic-capacitor-6x12mm.html)
 * J1 USB B female connector [Tayda](https://www.taydaelectronics.com/usb-type-b-female-connector-dip.html)
 * J2 2x3 2.54mm dupont header [Tayda](https://www.taydaelectronics.com/2x8-pin-2-54-mm-double-row-pin-header-strip.html)
 * J3 OR J4 Din-5 midi connector or stereo jack. You can techniaclly have both in the same PCB, DIN-5 on top and Jack on bottom [Tayda](https://www.taydaelectronics.com/5-pin-midi-connector-female-right-angle.html) or [Tayda](https://www.taydaelectronics.com/3-5mm-stereo-enclosed-socket-chassis-jack.html)
 * RV0\~RV5 Alps vertical linear potentiometer, any value from 1k to 1M [Tayda](https://www.taydaelectronics.com/100k-ohm-linear-taper-potentiometer-round-shaft-pcb-9mm.html) or [Tayda](https://www.taydaelectronics.com/100k-ohm-linear-taper-potentiometer-round-knurled-plastic-shaft-pcb-9mm.html)
 * SW0\~SW5 6mm pushbutton, any height you like [Tayda](https://www.taydaelectronics.com/tact-switch-6x6mm-5mm-through-hole-spst-no.html)
 * (Optional) M3 plastic spacers or M3 screws

## Writing the firmware

To burn the firmware you'll need an Arduino Uno board or any Arduino that can be used as ISP. 

 1. Upload the Arduino example "Arduino as ISP" to your arduino board.
 2. Unplug the Arduino, connect the ICSP header from the Arduino to the ICSP header of your MIDI controller board, EXCEPT the RST pin from the MIDI controller (third row, first column), which should be connected to the arduino board pin 10.

 ![icsp](https://i.imgur.com/4j5v6kI.png)

 3. Select the appropiate board/port in the Arduino IDE and go to tools > Burn bootloader. This bootloader will be overwritten in a second, but burning it now will activate some useful fuses inside the microcontroller, particularly the one selecting an external crystal oscillator. This needs to be done only once per chip.
 4. Open the firmware script "\Code\CardSizeMidiController\CardSizeMidiController.ino" or any custom script in the Arduino IDE and holding shift press the upload button, or select Sketch > Upload using uploader. After a few seconds of LED flashing the chip should have the firmware ready.

## How to use ()
Each button selects a different mode. The turned on LEDs signal the active midi channels.

 * When LEVEL mode is activated, each potentiometer change the Level Control Change (0x07) from channels 1 to 6.
 * When PAN mode is activated, each potentiometer change the Pan Control Change (0x0A) from channels 1 to 6.
 * When MOD mode is activated, each potentiometer change the Modulation Wheel Control Change (0x01) from channels 1 to 6.
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x1A,0x1B,0x1C,0x1D,0x1E,0x1F) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x66,0x67,0x68,0x69,0x70,0x71) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x72,0x73,0x74,0x75,0x76,0x77) in the active channel. 

In the CC modes the midi channel can be changed from 1 to 16 pressing multiple times the same button. The LEDs light up accordingly.

There are currently three double-button press settings:

 * Holding down buttons 1 and 2 makes the rightmost potentiometer control the value randomness from 0 (not randomness) to 127 (any value possible).
 * Holding down buttons 3 and 4 makes the rightmost potentiometer change the curve for all the MIDI messages from linear to logarithmic.
 * Holding down buttons 5 and 6 makes the rightmost potentiometer control the LED brightness.

Hold down a switch while powering up to select a different CC preset (1~6). Different presets can be flashed via code to accomodate to the CC received by any synthesizer or audio device. Not pressing any switch during boot will result in the default CC preset, which uses the forementioned undefined CC values.
