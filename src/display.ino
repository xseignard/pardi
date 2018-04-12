#include <utils.h>

void initDisplay() {
	dmd.setBrightness(255);
	dmd.selectFont(fixednums7x15);
	dmd.begin();
	blinkDisplay();
}

void blinkDisplay() {
	dmd.setBrightness(100);
	dmd.fillScreen(true);
	delay(500);
	dmd.clearScreen();
	delay(500);
	dmd.fillScreen(true);
	delay(500);
	dmd.clearScreen();
	dmd.setBrightness(255);
}

void updateDisplay() {
	int hours = numberOfHours(currentTime);
	int minutes = numberOfMinutes(currentTime);
	int seconds = numberOfSeconds(currentTime);
	String timeToDisplay = timeToString(hours, minutes, seconds);
	Serial.println(timeToDisplay);
	dmd.drawString(0, 2, timeToDisplay);
}

String timeToString(int hours, int minutes, int seconds) {
	String str = "";
	str += print(hours);
	str += ":";
	str += print(minutes);
	str += ":";
	str += print(seconds);
	return str;
}

String print(byte digits){
	String result = "";
	if(digits < 10) {
		result += "0";
		result += digits;
	} else result += digits;
	return result;
}
