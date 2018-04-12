#include <Wii.h>
// #include <usbhub.h>
#include <SPI.h>
#include <elapsedMillis.h>
#include <DMD2.h>
#include <fixednums7x15.h>

// DMD stuff
#define DISPLAYS_ACROSS 2
#define DISPLAYS_DOWN 1
#define DISPLAYS_BPP 1
// nOE, A, B, SCK, CLK, R
SoftDMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN, A2, A5, A4, A3, A0, A1);

// wiimote configuration
USB usb;
// USBHub hub(&usb);
BTD btd(&usb);
// pair the first time, after it's not needed
// WII wii(&btd, PAIR);
WII wii(&btd);

// time
elapsedMillis timeElapsed;
const long H = 12L;
const long M = 15L;
const long S = 00L;
const unsigned long BEGINNING_TIME = H * 3600L + M * 60L + S;
unsigned long currentTime = BEGINNING_TIME;
int step = 1;

// flags
bool firstConnect = true;
bool forward = true;

// interval timing for display
const int DEFAULT_INTERVAL_INDEX = 7;
int currentIntervalIndex = DEFAULT_INTERVAL_INDEX;
const int INTERVAL_SIZE = 12;
const unsigned int intervals[INTERVAL_SIZE] = {
	1,
	10,
	50,
	100,
	250,
	500,
	750,
	1000,
	1500,
	2000,
	3000,
	5000
};
unsigned int displayInterval = intervals[currentIntervalIndex];

// changing interval timing
elapsedMillis intervalElapsed;
unsigned int lerpInterval = 1000;

enum Mode {
	NORMAL,
	PAUSE,
	INCREASE,
	DECREASE,
	TRIPPY,
	DAY_BEFORE,
	LOOP
};
Mode mode = PAUSE;

void setup() {
	Serial.begin(115200);
	randomSeed(analogRead(0));
	initDisplay();
	delay(1000);
	initWii();
	delay(1000);
}

void loop() {
	handleWii();
	updateInterval();
	if (timeElapsed > displayInterval && mode != PAUSE) {
		updateTime();
		updateDisplay();
		timeElapsed = 0;
	}
}
