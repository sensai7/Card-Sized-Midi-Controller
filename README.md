# Card Size Midi Controller
 Standard card sized MIDI controller, for level, pan, modulation wheel and control changes. Both hardware and software are open source, you can modify and use as you please.

![Board](https://i.imgur.com/lAB1ZPd.png)

## Ordering your own board
This repository will include the necessary files to order your own board with the SMT components pre-soldered from JLCPCB's assembly service. To do so, follow this: 

 1 - go to their order page ![LINK](cart.jlcpcb.com/quote) and upload the zipped gerber files. The default options should be fine, but you can customize your own board as you wish, the only thing I recommed changing is under "Remove Order Number" to "Specify a location"
 ... [TBD]

## Adding the rest of components (BOM)

! each part links to the particular component in Tayda, but can be sourced from anywhere else. [TBD]

 * C1 10u
 * C2 100u
 * J1 USB C female connector
 * J2 2x3 2.54mm dupont header
 * J3 OR J4 Din-5 midi connector or stereo jack
 * RV0\~RV5 Alps vertical potentiometer, any value from 1k to 1M
 * SW0\~SW5 6mm pushbutton, any height you like
 * (Optional) M3 plastic spacers

## Writing the firmware

To burn the firmware you'll need an Arduino Uno board or any Arduino that can be used as ISP. 

 1- Upload the Arduino example "Arduino as ISP" to your arduino board.
 2- Unplug the Arduino, connect the ICSP header from the Arduino to the ICSP header of your MIDI controller board, EXCEPT the RST pin from the MIDI controller (third row, first column), which should be connected to the arduino board pin 10.

 [TBD] sketch

 3- Select the appropiate board/port in the Arduino IDE and go to tools > Burn bootloader. This bootloader will be overwritten in a second, but burning it now will activate some useful fuses inside the microcontroller, particularly the one selecting an external crystal oscillator. This needs to be done only once per chip.
 4- Open the firmware script "\Code\CardSizeMidiController\CardSizeMidiController.ino" or any custom script in the Arduino IDE and holding shift press the upload button, or select Sketch > Upload using uploader. After a few seconds of LED flashing the chip should have the firmware ready.

## How to use ()
Each button selects a different mode. The turned on LEDs signal the active midi channels.

 * When LEVEL mode is activated, each potentiometer change the Level Control Change (0x07) from channels 1 to 6.
 * When PAN mode is activated, each potentiometer change the Pan Control Change (0x0A) from channels 1 to 6.
 * When MOD mode is activated, each potentiometer change the Modulation Wheel Control Change (0x01) from channels 1 to 6.
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x1A,0x1B,0x1C,0x1D,0x1E,0x1F) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x66,0x67,0x68,0x69,0x70,0x71) in the active channel. 
 * When CC1 mode is activated, each potentiometer change a different unassigned CC value (0x72,0x73,0x74,0x75,0x76,0x77) in the active channel. 

In the CC modes the midi channel can be changed from 1 to 6 pressing multiple times the same button.