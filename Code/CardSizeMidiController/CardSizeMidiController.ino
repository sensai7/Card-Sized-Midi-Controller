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
int index = 0; //index is shared
int potRead[BUFFER][SIX];
int potPort[SIX] = {POT0,POT1,POT2,POT3,POT4,POT5};
int currentMedian[SIX] = {0,0,0,0,0,0};
int previousMedian[SIX] = {0,0,0,0,0,0};
int sortBuff[BUFFER];

//Leds
int ledBrightness = 10; //3.9%
int ledPort[SIX] = {LED0,LED1,LED2,LED3,LED4,LED5};
int ledStatus[SIX] = {ledBrightness,ledBrightness,ledBrightness,ledBrightness,ledBrightness,ledBrightness};

//Switches
int swPort[SIX] = {SW0,SW1,SW2,SW3,SW4,SW5};
int currentButtonState[SIX] = {0,0,0,0,0,0};
int previousButtonState[SIX] = {0,0,0,0,0,0};
int pressedButton[SIX] = {0,0,0,0,0,0};

//undefined CC banks
int CC1[SIX] = {0x1A,0x1B,0x1C,0x1D,0x1E,0x1F};
int CC2[SIX] = {0x66,0x67,0x68,0x69,0x70,0x71};
int CC3[SIX] = {0x72,0x73,0x74,0x75,0x76,0x77};

//general
int mode = 0;
int channel = 0;

void setup() {
	TCCR1B = TCCR1B & B11111000 | B00000010;
	TCCR2B = TCCR2B & B11111000 | B00000011;
	Serial.begin(31250);
	for(int i = 0; i < SIX; i++){
		pinMode(swPort[i], INPUT_PULLUP);
		pinMode(ledPort[i], OUTPUT);
	}
	updateLeds(ledPort, ledStatus);  
}

void loop() {
	updateButtons(swPort, currentButtonState, previousButtonState);
	pushedButtons(pressedButton, currentButtonState, previousButtonState);
	for (int i = 0; i < SIX; i++){
		if(pressedButton[i]){
			if(i == mode)
				channel = (channel+1) % SIX;
			else
				mode = i;
			switch (mode){
				case 0:
				allLedsOn(ledStatus);
				updateLeds(ledPort, ledStatus);
				break;
				case 1:
				allLedsOn(ledStatus);
				updateLeds(ledPort, ledStatus);
				break;
				case 2:
				allLedsOn(ledStatus);
				updateLeds(ledPort, ledStatus);
				break;
				case 3:
				allLedsOff(ledStatus);
				ledStatus[channel]= ledBrightness;
				updateLeds(ledPort, ledStatus);
				break;
				case 4:
				allLedsOff(ledStatus);
				ledStatus[channel]= ledBrightness;
				updateLeds(ledPort, ledStatus);
				break;
				case 5:
				allLedsOff(ledStatus);
				ledStatus[channel]= ledBrightness;
				updateLeds(ledPort, ledStatus);
				break;
			}
		}
	}

	switch(mode){
		case 0:
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(i, 0x07, currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);
		break; 

		case 1: //Pan mode
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(i, 0x0A, currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);
		break; 

		case 2: //Mod mode
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(i, 0x01, currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);
		break;

		case 3: //CC1 mode
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(channel, CC1[i], currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);

		break;

		case 4: //CC2 mode
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(channel, CC2[i], currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);
		break;

		case 5: //CC3 mode
		for (int i = 0; i < SIX; i++){
			previousMedian[i] = currentMedian[i];
			potRead[index][i] = analogRead(potPort[i]);
			copyRow(sortBuff, potRead, i);
			currentMedian[i] = map(median(sortBuff, BUFFER), 0, 1023, 0, 127);
			if (currentMedian[i] != previousMedian[i]){
				midiCCsend(channel, CC3[i], currentMedian[i]);
			}
		}
		index = (index +1) % BUFFER;
		delay(10);
		break;
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


void updateButtons(int * buttons, int * current, int * previous){
	for(int i = 0; i < SIX; i++){
		previous[i] = current[i];
		current[i] = digitalRead(buttons[i]);
	}
}

void pushedButtons(int * buttons, int * current, int * previous){
	for(int i = 0; i < SIX; i++){
		if (previous[i] && !current[i]){
			buttons[i] = 1;
		}
		else
			buttons[i] = 0;
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
