/*
 * globals.h

 *
 *  Created on: 20 nov. 2016
 *      Author: tgtob
 */

#ifndef SRC_GLOBALS_H_
#define SRC_GLOBALS_H_

#include <Arduino.h>
#include <Servo.h>
#include "Timer4.h"
#include "settings.h"
#include "scheduler.h"
#include "SensorData.h"
//#include "Parameters.h"
#include "Com.h"

// Global objects
extern Servo turn;
//extern Parameters pms;
extern Timer4 t4;
extern Com com;
extern Scheduler s;
extern SensorData<uint16_t> s1;
extern SensorData<uint16_t> s2;
extern SensorData<uint16_t> s3;
extern bool drive_active;
//VL53L0X tof_sensor;
//Tof_sensor tof;

// Global variables
extern int turn_value;
extern uint8_t fw;
extern uint8_t bw;

extern uint16_t FW_SPEED;
extern uint16_t sensor1;
extern int trim1;
extern int trim2;

extern int debug_act;
extern uint16_t debug_act_s3;
extern uint16_t debug_dev_s1;


void debug_print(const char * s);
void debug_print(String s) ;



#endif /* SRC_GLOBALS_H_ */
