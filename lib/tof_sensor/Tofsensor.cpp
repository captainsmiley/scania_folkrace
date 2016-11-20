/*
 * Tofsensor.cpp
 *
 *  Created on: 16 nov. 2016
 *      Author: tgtob
 */

#include "Tofsensor.h"
#include <Arduino.h>
#include <Wire.h>

	VL53L0X_Error Status;
	VL53L0X_Dev_t MyDevice;
	VL53L0X_Dev_t *pMyDevice;
	VL53L0X_Version_t           Version;
	VL53L0X_Version_t                  *pVersion;
	VL53L0X_DeviceInfo_t                DeviceInfo;

Tof_sensor::Tof_sensor()
//pMyDevice(&MyDevice),
//pVersion(&Version)

{
	// TODO Auto-generated constructor stub
	VL53L0X_i2c_init();

	Status = VL53L0X_ERROR_NONE;

	// Initialize Comms
	pMyDevice->I2cDevAddr      = 0x52;






}

void Tof_sensor::device_init()
{
	if(Status == VL53L0X_ERROR_NONE)
	{
		//Serial.println("Call of VL53L0X_DataInit\n");
		Status = VL53L0X_DataInit(&MyDevice); // Data initialization
	}

}

void Tof_sensor::device_info()
{




	        if(Status == VL53L0X_ERROR_NONE)
	        {
	        	//Serial.println("get dev info");
	            Status = VL53L0X_GetDeviceInfo(&MyDevice, &DeviceInfo);
	        }
	        if(Status == VL53L0X_ERROR_NONE)
	        {
	            //Serial.println("VL53L0X_GetDeviceInfo:");
	            //Serial.println(DeviceInfo.ProductRevisionMajor);
	            //Serial.println(DeviceInfo.ProductRevisionMinor);
	            //Serial.println(DeviceInfo.Name);
	            //Serial.println(DeviceInfo.ProductId);
	            //Serial.println(DeviceInfo.Type);
	            //Serial.println("Device Name: " + String( DeviceInfo.Name));
	            //printf("Device Type : %s\n", DeviceInfo.Type);
	            //jprintf("Device ID : %s\n", DeviceInfo.ProductId);
	            //printf("ProductRevisionMajor : %d\n", DeviceInfo.ProductRevisionMajor);
	            //printf("ProductRevisionMinor : %d\n", DeviceInfo.ProductRevisionMinor);

	        }

}



Tof_sensor::~Tof_sensor() {
	// TODO Auto-generated destructor stub
}

