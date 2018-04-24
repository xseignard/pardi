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
	if (mode == LOOP) {
		currentTime = forward ? currentTime + 1 : currentTime - 1;
		if (
			(forward && currentTime - loopTimeStamp > 3) ||
			(!forward && loopTimeStamp - currentTime > 3)
		) {
			currentTime = loopTimeStamp;
		}
	}
	else currentTime = forward ? currentTime + 1 : currentTime - 1;
}
