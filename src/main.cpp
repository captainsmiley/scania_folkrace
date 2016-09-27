#include <Arduino.h>


void setup()
{
	Serial.begin(115200);
	Serial.println("Start of program");
}

void loop()
{
	Serial.println("main loop start");
	delay(1000);
	Serial.println("main loop end");
}

