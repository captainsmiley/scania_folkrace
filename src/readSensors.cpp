/*
 * readSensors.cpp


 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */

#include "readSensors.h"


ReadSensors::ReadSensors(uint32_t dt_p) :
		Task("Read sensors",dt_p)
{

}

ReadSensors::~ReadSensors() {}

void ReadSensors::setup()
{

}

void ReadSensors::run()
{
	s1.add(analogRead(SENSOR1_PIN));
	s2.add(analogRead(SENSOR2_PIN));
	s3.add(analogRead(SENSOR3_PIN));
	#if TRIM1
	trim1 = analogRead(TRIM1_PIN);
	#endif
	#if TRIM2
	trim2 = analogRead(TRIM2_PIN);
	#endif
}
