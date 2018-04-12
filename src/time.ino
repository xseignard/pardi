#include <utils.h>

void updateInterval() {
	if (intervalElapsed > lerpInterval) {
		switch (mode) {
			case INCREASE:
				currentIntervalIndex--;
				currentIntervalIndex = constrain(currentIntervalIndex, 0, INTERVAL_SIZE - 1);
				if (currentIntervalIndex == 0) step = 11;
				break;
			case DECREASE:
				currentIntervalIndex++;
				currentIntervalIndex = constrain(currentIntervalIndex, 0, INTERVAL_SIZE - 1);
				if (currentIntervalIndex == INTERVAL_SIZE - 3) step = 1;
				break;
			case TRIPPY:
				currentIntervalIndex = random(0, INTERVAL_SIZE - 1);
				step = random(-1000, 1000);
				break;
			default:
				break;
		}
		displayInterval = intervals[currentIntervalIndex];
		intervalElapsed = 0;
	}
}
void updateTime() {
	// clockwise / counterclockwise
	if (forward) {
		currentTime += step;
		if (
			mode == LOOP &&
			numberOfSeconds(currentTime) == 0
		) currentTime -= 60;
	}
	else {
		currentTime -= step;
		if (
			mode == LOOP &&
			numberOfSeconds(currentTime) == 59
		) currentTime += 60;
	}
}
