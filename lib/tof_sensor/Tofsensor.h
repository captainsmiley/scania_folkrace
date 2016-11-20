/*
 * Tofsensor.h
 *
 *  Created on: 16 nov. 2016
 *      Author: tgtob
 */

#ifndef LIB_TOF_SENSOR_TOFSENSOR_H_
#define LIB_TOF_SENSOR_TOFSENSOR_H_


#include "vl53l0x_api.h"
#include "vl53l0x_platform.h"

class Tof_sensor {
public:
	Tof_sensor();
	void device_info();
	void device_init();
	virtual ~Tof_sensor();

private:
};

#endif /* LIB_TOF_SENSOR_TOFSENSOR_H_ */
