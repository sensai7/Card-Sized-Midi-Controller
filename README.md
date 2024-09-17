# Card Size Midi Controller
 Standard card sized MIDI controller, for level, pan, modulation wheel and control changes. Both hardware and software are open source, you can modify and use as you please.

![Board](https://i.imgur.com/lhvjsof.png)

## Ordering your own board
### Tindie

This device is available at [Tindie](https://www.tindie.com/products/sensai7/card-sized-midi-controller/).

### JLCPCB
This repository includes the necessary files to order your own board with the SMT components pre-soldered from JLCPCB's assembly service. To do so, follow this: 

1. from this Github page click `Code > download zip`.
2. Uncompress the zip.
3. Go to jlcpcb.com or any other pcb maker. I'll assume you're using JLC for the next steps.
4. Select `instant quote` and when prompted to select a gerber file, select the file `\Kicad\CardSizeMidiController\production\CardSizeMidiController.zip`. From here there will be a lot of options but most of them can be left as default. The only “mandatory” change is `Mark on PCB` which should be changed to `Order Number (Specify Position)`. You can also optionaly change:
* the quantity (5 by default)
* the color, which is green by default.
* PCB thickness can also be changed at will but I think too thin or too thick and the price increases a little bit.

If you go like this and checkout the order you will be buying the naked PCBs with nothing mounted. If you want at least to mount the SMT components then:

1. Switch the PCB Assembly on at the bottom of the menu in the JLC order page.
2. Everything can be left on the default values (Top side, Economic, etc) but you can choose to assemble just a couple of boards instead of all of them. It’ll save you some money but you’ll be left with 3 naked boards.
3. Hit next twice and you'll be asked to upload a BOM file and a CPL file. They’re both in the same folder as the gerber zip from before, they’re respectively `bom.csv` and `positions.csv`.
4. Go to the next screen and you’ll see a table with all the components that are about to be assembled.
5. Next screen will show you a 3D render of the board with the components. For some reason Kicad doesn't export all well the positions and angles, so keep an eye on where the things are being placed. Particularly the position of the USB connector, the potentiometers, and the angle of the push buttons.
6. After that screen you can continue until ordering them.

## Writing the firmware

To burn the firmware you'll need an Arduino Uno board or any Arduino that can be used as ISP. 

 1. Upload the Arduino example "Arduino as ISP" to your arduino board.
 2. Unplug the Arduino, connect the ICSP header from the Arduino to the ICSP header of your MIDI controller board, EXCEPT the RST pin from the MIDI controller (third row, first column), which should be connected to the arduino board pin 10.

 ![icsp](https://i.imgur.com/4j5v6kI.png)

 3. Check which processor you have. If you have an AtMega328P you can continue, if it's a AtMega328PB you'll need to [change the signature](https://www.instructables.com/How-to-Fix-Expected-Signature-for-ATMEGA328P-Is-1E/) in the avrdude config file.
 3. In tools > Programmer be sure "Arduino as ISP" is selected with a check mark, or otherwhise the following actions will be executed in the Arduino board instead of the target board.
 4. Select the appropiate board/port in the Arduino IDE and go to tools > Burn bootloader. This bootloader will be overwritten in a second, but burning it now will activate some useful fuses inside the microcontroller, particularly the one selecting an external crystal oscillator. This needs to be done only once per chip.
 5. Open the firmware script "\Code\CardSizeMidiController\CardSizeMidiController.ino" or any custom script in the Arduino IDE and holding shift press the upload button, or select Sketch > Upload using uploader. After a few seconds of LED flashing the chip should have the firmware ready.

## How to use ()
Each button selects a different mode. The turned on LEDs signal the active midi channels.

 * When LEVEL mode is activated, each potentiometer change the Level Control Change (0x07) from channels 1 to 6.
 * When PAN mode is activated, each potentiometer change the Pan Control Change (0x0A) from channels 1 to 6.
 * When MOD mode is activated, each potentiometer change the Modulation Wheel Control Change (0x01) from channels 1 to 6.
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x1A,0x1B,0x1C,0x1D,0x1E,0x1F) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x66,0x67,0x68,0x69,0x70,0x71) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x72,0x73,0x74,0x75,0x76,0x77) in the active channel. 

In the CC modes the midi channel can be changed from 1 to 16 pressing multiple times the same button. The LEDs light up accordingly.
In the LEVEL, PAN, and MOD modes, subsequent presses of the mode button will toggle the active MIDI channels from 1-6 to 7-12.

There are currently three double-button press settings:

 * Holding down buttons 1 and 2 makes the rightmost potentiometer control the value randomness from 0 (not randomness) to 127 (any value possible).
 * Holding down buttons 3 and 4 makes the rightmost potentiometer change the curve for all the MIDI messages from linear to logarithmic.
 * Holding down buttons 5 and 6 makes the rightmost potentiometer control the LED brightness.

Hold down a switch while powering up to select a different CC preset (1~6). Different presets can be flashed via code to accomodate to the CC received by any synthesizer or audio device. Not pressing any switch during boot will result in the default CC preset, which uses the forementioned undefined CC values.

Default presets:

 0. (default) Undefined CC. Use this preset to use along MIDI learn in your devices.
 1. Korg Volca FM preset
 2. Korg Volca Keys preset
 3. Korg Volca Bass preset
 4. Korg Volca Nubass preset
 5. Korg Volca Kick preset
 6. Korg Volca Sample preset
