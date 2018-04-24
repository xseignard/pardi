void initWii()
{
	if (usb.Init() == -1)
	{
		Serial.print(F("Failed to start USB host"));
		while (1)
			;
	}
	Serial.println(F("Wiimote started"));
}
void handleWii()
{
	// USB process
	usb.Task();
	// do something only if wiimote is connected
	if (wii.wiimoteConnected)
	{
		// vibrate to notify the connection
		if (firstConnect)
		{
			vibrate(1000);
			firstConnect = false;
		}

		// top button: acceleration mode
		if (wii.getButtonClick(UP))
		{
			Serial.println(F("UP"));
			mode = INCREASE;
			vibrate(100);
		}
		// right button: normal mode
		else if (wii.getButtonClick(RIGHT))
		{
			Serial.println(F("RIGHT"));
			mode = NORMAL;
			step = 1;
			currentIntervalIndex = DEFAULT_INTERVAL_INDEX;
			forward = true;
			vibrate(100);
		}
		// bottom button: slowdown mode
		else if (wii.getButtonClick(DOWN))
		{
			Serial.println(F("DOWN"));
			mode = DECREASE;
			vibrate(100);
		}
		// left button: counter clock mode
		else if (wii.getButtonClick(LEFT))
		{
			Serial.println(F("LEFT"));
			mode = NORMAL;
			step = 1;
			currentIntervalIndex = DEFAULT_INTERVAL_INDEX;
			forward = false;
			vibrate(100);
		}
		// home button: back to beginning
		else if (wii.getButtonClick(HOME))
		{
			Serial.println(F("HOME"));
			mode = PAUSE;
			step = 1;
			currentIntervalIndex = DEFAULT_INTERVAL_INDEX;
			currentTime = BEGINNING_TIME;
			vibrate(100);
		}
		// plus button: increase speed
		else if (wii.getButtonClick(PLUS))
		{
			Serial.println(F("PLUS"));
			currentIntervalIndex--;
			currentIntervalIndex = constrain(currentIntervalIndex, 0, INTERVAL_SIZE - 1);
			vibrate(100);
		}
		// minus button: decrease speed
		else if (wii.getButtonClick(MINUS))
		{
			Serial.println(F("MINUS"));
			currentIntervalIndex++;
			currentIntervalIndex = constrain(currentIntervalIndex, 0, INTERVAL_SIZE - 1);
			vibrate(100);
		}
		// A button: pause mode
		else if (wii.getButtonClick(A))
		{
			Serial.println(F("A"));
			mode = PAUSE;
			step = 1;
			vibrate(100);
		}
		// B button: distortion mode
		else if (wii.getButtonClick(B))
		{
			Serial.println(F("B"));
			mode = TRIPPY;
			vibrate(100);
		}
		// 1 button: day before show
		else if (wii.getButtonClick(ONE))
		{
			Serial.println(F("ONE"));
			mode = DAY_BEFORE;
			vibrate(100);
		}
		// 2 button: minute loop
		else if (wii.getButtonClick(TWO))
		{
			Serial.println(F("TWO"));
			loopTimeStamp = currentTime;
			mode = LOOP;
			vibrate(100);
		}
	}
}

void vibrate(int duration)
{
	wii.setRumbleOn();
	delay(duration);
	wii.setRumbleOff();
}
