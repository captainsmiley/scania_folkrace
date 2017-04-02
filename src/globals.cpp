/*
 * globals.cpp
 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */
#include "globals.h"

// Global objects
Servo turn;
Timer4 t4;
Com com;
Scheduler s;
SensorData<uint16_t> s1(10);
SensorData<uint16_t> s2(10);
SensorData<uint16_t> s3(10);
bool drive_active = true;
//VL53L0X tof_sensor;
//Tof_sensor tof;

// Global variables
int turn_value = 90;
uint8_t fw = 0;
uint8_t bw = 0;

uint16_t FW_SPEED = 400;
uint16_t sensor1 = 0;
int trim1 = -1;
int trim2 = -1;

int debug_act = 0;
uint16_t debug_act_s3 = 0;
uint16_t debug_dev_s1 = 0;

void debug_print(const char * s) {
	#ifdef SERIAL_DEBUG
	Serial.println(s);
	#endif
}
void debug_print(String s) {
	#ifdef SERIAL_DEBUG
	char s_buff[22];
	s.toCharArray(s_buff,22);
	com.outln(s_buff);
	#endif
}


