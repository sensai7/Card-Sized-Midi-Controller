#define SW0 2	
#define SW1 4
#define SW2 7
#define SW3 8
#define SW4 12
#define SW5 13
#define POT0 A0
#define POT1 A1
#define POT2 A2
#define POT3 A3
#define POT4 A4
#define POT5 A5
#define LED0 3
#define LED1 5
#define LED2 6
#define LED3 9
#define LED4 10
#define LED5 11
#define SIX 6

//Pots
#define BUFFER 11
#define BUFFERSIZE 22 // BUFFER * sizeof(int)
int logResponse[128] =  {0, 18, 29, 37, 42, 47, 51, 55, 58, 61, 63, 66, 68, 70, 71, 
						73, 75, 76, 78, 79, 80, 82, 83, 84, 85, 86, 87, 88, 89, 90, 
						91, 91, 92, 93, 94, 95, 95, 96, 97, 97, 98, 99, 99, 100, 
						100, 101, 102, 102, 103, 103, 104, 104, 105, 105, 106, 106, 
						107, 107, 108, 108, 108, 109, 109, 110, 110, 111, 111, 111, 
						112, 112, 112, 113, 113, 114, 114, 114, 115, 115, 115, 116, 
						116, 116, 117, 117, 117, 118, 118, 118, 118, 119, 119, 119, 
						120, 120, 120, 120, 121, 121, 121, 121, 122, 122, 122, 123, 
						123, 123, 123, 124, 124, 124, 124, 124, 125, 125, 125, 125, 
						126, 126, 126, 126, 127, 127, 127, 127, 127, 128, 128, 128};
int index = 0; //index is shared
int potRead[BUFFER][SIX];
int potPort[SIX] = {POT0, POT1, POT2, POT3, POT4, POT5};
int currentMedian[SIX] = {0, 0, 0, 0, 0, 0};
int previousMedian[SIX] = {0, 0, 0, 0, 0, 0};
int sortBuff[BUFFER];

//Leds
int ledBrightness = 10; //3.9%
int ledPort[SIX] = {LED0, LED1, LED2, LED3, LED4, LED5};
int ledStatus[SIX];

//Switches
int swPort[SIX] = {SW0, SW1, SW2, SW3, SW4, SW5};
int currentButtonState[SIX] = {0, 0, 0, 0, 0, 0};
int previousButtonState[SIX] = {0, 0, 0, 0, 0, 0};
int pressedButton[SIX] = {0, 0, 0, 0, 0, 0};

//CC banks
int * CC1;
int * CC2;
int * CC3;

//Undefined CC
int undefinedCC1[SIX] = {0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};
int undefinedCC2[SIX] = {0x66, 0x67, 0x68, 0x69, 0x70, 0x71};
int undefinedCC3[SIX] = {0x72, 0x73, 0x74, 0x75, 0x76, 0x77};

//preset CC
int volcaFMCC1[SIX] = {40, 41, 42, 43, 44, 45}; //TRANSPOSE, VELOCITY, MODULATOR ATTACK, MODLULATOR DECAY, CARRIER ATTACK, CARRIER DECAY
int volcaFMCC2[SIX] = {46, 47, 48, 49, 50, 0x01}; //LFO RATE, LFO PICTH DEPTH, ALGORITHM, ARP TYPE, ARP DIV
int volcaFMCC3[SIX] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

int volcaKeysCC1[SIX] = {5, 11, 40, 41, 42, 43}; //PORTAMENTO, EXPRESSION, VOICE, OCTAVE, DETUNE, VCO EG INT
int volcaKeysCC2[SIX] = {44, 45, 46, 47, 48, 49}; //CUTOFF, VCF EG INT, LFO RATE, LFO PITCH, LFO CUTOFF INT, EG ATTACK
int volcaKeysCC3[SIX] = {50, 51, 52, 53, 0x01, 0x01}; //EG DECAY/RELEASE, EG SUSTAIN, DELAY TIME, DELAY FEEDBACK

int volcaBassCC1[SIX] = {5, 11, 40, 41, 42, 43}; //SLIDE TIME, EXPRESSION, OCTAVE, LFO RATE, LFO INT, VCO PITCH 1
int volcaBassCC2[SIX] = {44, 45, 46, 47, 48, 49}; //VCO PITCH 2, VCO PITCH 3, EG ATTACK, EG DECAY/RELEASE, CUTOFF EG INT, GATE TIME
int volcaBassCC3[SIX] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

int volcaNubassCC1[SIX] = {40, 41, 42, 43, 44, 45}; //VTO PITCH, VTO SATURATION, VTO LEVEL, VCF CUTOFF, VCF PEAK, VCF ATTACK
int volcaNubassCC2[SIX] = {46, 47, 48, 49, 50, 0x01}; //VCF DECAY, VCF EG INT, ACCENT, LFO RATE, LFO INT
int volcaNubassCC3[SIX] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

int volcaKickCC1[SIX] = {40, 41, 42, 43, 44, 45}; //PULSE COLOUR, PULSE LEVEL, AMP ATTACK, AMP DECAY, DRIVE, TONE
int volcaKickCC2[SIX] = {46, 47, 48, 49, 0x01, 0x01}; //RESONATOR PITCH, RESONATOR BEND, RESONATOR TIME, ACCENT
int volcaKickCC3[SIX] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

int volcaSampleCC1[SIX] = {40, 41, 42, 43, 44, 45}; //SAMPLE START POINT, SAMPLE LENGTH, HI CUT, SPEED, PITCH EG INT, PITCH EG ATTACK
int volcaSampleCC2[SIX] = {46, 47, 48, 0x01, 0x01, 0x01}; //PITCH EG DECAY, AMP EG ATTACK, AMP EG DECAY
int volcaSampleCC3[SIX] = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01};

//general
int mode = -1;
int channel = 0;
int randomness = 0;
int logness = 0;
int preset = 0;
int secondPage = 0;

//function prototypes
void updateLeds(int * leds, int * stat);
void allLedsOn(int * stat);
void allLedsOff(int * stat);
void channel2led(void);
void updateButtons(int * buttons, int * current, int * previous);
void pushedButtons(int * buttons, int * current, int * previous);
int median(int * a,int n);
void swap(int *p,int *q);
void copyRow(int *destMatrix, int srcMatrix[][SIX], int ind);
void midiCCsend(int channel, int cmd, int value);
void flash(int led, int brightness, int mill, int times);

//TODO 36cc for presets
//TODO glide
//TODO snap to value or not
//TODO channels 13-16 for level, pan and mod

void setup() {
	delay(1000);
	Serial.begin(31250);
	for(int i = 0; i < SIX; i++){
		pinMode(swPort[i], INPUT_PULLUP);
		pinMode(ledPort[i], OUTPUT);
	}
	updateLeds(ledPort, ledStatus); 

	//preset detect TODO: change to multi dimensional matrix
	updateButtons(swPort, currentButtonState, previousButtonState);
	for(int i = 0; i < SIX; i++){
		if(!currentButtonState[i]){
			preset = i + 1;
		}
	} 
	
	switch (preset){
		case 1:
			CC1 = volcaFMCC1;
			CC2 = volcaFMCC2;
			CC3 = volcaFMCC3;
		break;
		case 2:
			CC1 = volcaKeysCC1;
			CC2 = volcaKeysCC2;
			CC3 = volcaKeysCC3;
		break;
		case 3:
			CC1 = volcaBassCC1;
			CC2 = volcaBassCC2;
			CC3 = volcaBassCC3;
		break;
		case 4:
			CC1 = volcaNubassCC1;
			CC2 = volcaNubassCC2;
			CC3 = volcaNubassCC3;
		break;
		case 5:
			CC1 = volcaKickCC1;
			CC2 = volcaKickCC2;
			CC3 = volcaKickCC3;
		break;
		case 6:
			CC1 = volcaSampleCC1;
			CC2 = volcaSampleCC2;
			CC3 = volcaSampleCC3;
		break;
		default:
			CC1 = undefinedCC1;
			CC2 = undefinedCC2;
			CC3 = undefinedCC3;
		break;
	}
	if (preset >= 1){
		flash(ledPort[preset-1], ledBrightness, 100, 5);
	}

}

void loop() {
	updateButtons(swPort, currentButtonState, previousButtonState);
	pushedButtons(pressedButton, currentButtonState, previousButtonState);
	int settingFlag = 0;
	
	//double button presses
	// 1+2 Randomness
	if(!currentButtonState[0] && !currentButtonState[1]){
		randomness = map(analogRead(potPort[5]), 0, 1023, 0, 127);
		settingFlag = 1;
	}
	// 3+4 Logness
	if(!currentButtonState[2] && !currentButtonState[3]){
		logness = map(analogRead(potPort[5]), 0, 1023, 0, 255);
		settingFlag = 1;
	}
	// 5+6 LED brightness
	if(!currentButtonState[4] && !currentButtonState[5]){
		ledBrightness = map(analogRead(potPort[5]), 0, 1023, 0, 255);
		allLedsOn(ledStatus);
		updateLeds(ledPort, ledStatus);  
		settingFlag = 1;
	}
	
	//single button presses
	if(!settingFlag){
		for (int i = 0; i < SIX; i++){
			if(pressedButton[i]){
				if(i == mode)
					if(mode >= 3 && mode <= 5)
						channel = (channel + 1) % 16;
					else
						secondPage = (!secondPage) * 6;
				else
					mode = i;
				switch (mode){
					case 0:
					allLedsOn(ledStatus);
					ledStatus[secondPage/6] = 0;
					updateLeds(ledPort, ledStatus);
					break;
					case 1:
					allLedsOn(ledStatus);
					ledStatus[secondPage/6] = 0;
					updateLeds(ledPort, ledStatus);
					break;
					case 2:
					allLedsOn(ledStatus);
					ledStatus[secondPage/6] = 0;
					updateLeds(ledPort, ledStatus);
					break;
					case 3:
					allLedsOff(ledStatus);
					channel2led();
					updateLeds(ledPort, ledStatus);
					break;
					case 4:
					allLedsOff(ledStatus);
					channel2led();
					updateLeds(ledPort, ledStatus);
					break;
					case 5:
					allLedsOff(ledStatus);
					channel2led();
					updateLeds(ledPort, ledStatus);
					break;
				}
			}
		}

		//midi operations
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				int finalValue; 
				int variation = random(-randomness, randomness);
				finalValue = (currentMedian[i] * (255 - logness))/255 + (logResponse[currentMedian[i]] * logness)/255 + variation;
				if(variation > 0 && finalValue > 127){
					finalValue = 127;
				}
				if(variation < 0 && finalValue < 0){
					finalValue = 0;
				}
				switch (mode){
					case 0:
						midiCCsend(i + secondPage, 0x07, finalValue);
					break;
					case 1:
						midiCCsend(i + secondPage, 0x0A, finalValue);
					break;
					case 2:
						midiCCsend(i + secondPage, 0x01, finalValue);
					break;
					case 3:
						midiCCsend(channel, CC1[i], finalValue);
					break;
					case 4:
						midiCCsend(channel, CC2[i], finalValue);
					break;
					case 5:
						midiCCsend(channel, CC3[i], finalValue);
					break;
				}
			}
		}
		index = (index +1) % BUFFER;
		delay(5);
	}
}

void updateLeds(int * leds, int * stat){
	int i;
	for(i = 0; i < SIX; i++){
		analogWrite(leds[i], stat[i]);
	}
}

void allLedsOn(int * stat){
	int i;
	for(i = 0; i < SIX; i++){
		stat[i] = ledBrightness;
	}
}

void allLedsOff(int * stat){
	int i;
	for(i = 0; i < SIX; i++){
		stat[i] = 0;
	}
}

void channel2led(void){
	if (channel < 6){
		ledStatus[channel]= ledBrightness;
	}	
	else{
		switch(channel){
			case 6:
				ledStatus[0] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 7:
				ledStatus[1] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 8:
				ledStatus[2] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 9:
				ledStatus[3] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;
			
			case 10:
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 11:
				ledStatus[0] = ledBrightness;
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;
			
			case 12:
				ledStatus[1] = ledBrightness;
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 13:
				ledStatus[2] = ledBrightness;
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;
			
			case 14:
				ledStatus[3] = ledBrightness;
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;

			case 15:
				ledStatus[0] = ledBrightness;		
				ledStatus[3] = ledBrightness;
				ledStatus[4] = ledBrightness;
				ledStatus[5] = ledBrightness;
			break;
		}
	}
}

void updateButtons(int * buttons, int * current, int * previous){
	for(int i = 0; i < SIX; i++){
		previous[i] = current[i];
		current[i] = digitalRead(buttons[i]);
	}
}

void pushedButtons(int * buttons, int * current, int * previous){
	for(int i = 0; i < SIX; i++){
		(previous[i] && !current[i]) ? buttons[i] = 1 : buttons[i] = 0;
	}
}

int median(int * a,int n) { 
   int i,j;
   for(i = 0;i < n-1;i++) {
      for(j = 0;j < n-i-1;j++) {
         if(a[j] > a[j+1])
            swap(&a[j],&a[j+1]);
      }
   }
   n = (n+1) / 2 - 1;
   return a[n];
}

void swap(int *p,int *q) {
   int t;
   t=*p; 
   *p=*q; 
   *q=t;
}

void copyRow(int *destMatrix, int srcMatrix[][SIX], int ind){
	for (int i = 0; i < BUFFER; i++){
		destMatrix[i] = srcMatrix[i][ind];
	}
}

void midiCCsend(int channel, int cmd, int value) {
	Serial.write(0xb0 | channel);
	Serial.write(cmd);
	Serial.write(value);
}

void flash(int led, int brightness, int mill, int times){
	for (int ind = 0; ind < times; ind++){
		analogWrite(led, brightness);
		delay(mill);
		digitalWrite(led, 0);
		delay(mill);	
	}
}
	
	
