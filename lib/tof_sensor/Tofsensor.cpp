/*
 * Tofsensor.cpp
 *
 *  Created on: 16 nov. 2016
 *      Author: tgtob
 */

#include "Tofsensor.h"
#include <Arduino.h>
#include <Wire.h>

#include "core/inc/vl53l0x_api.h"
#include "platform/inc/vl53l0x_platform.h"

Tof_sensor::Tof_sensor() {
	// TODO Auto-generated constructor stub
	VL53L0_i2c_init();
	VL53L0X_Error Status = VL53L0X_ERROR_NONE;
	VL53L0X_Dev_t MyDevice;
	    VL53L0X_Dev_t *pMyDevice = &MyDevice;
	    VL53L0X_Version_t                   Version;
	    VL53L0X_Version_t                  *pVersion   = &Version;
	    VL53L0X_DeviceInfo_t                DeviceInfo;


	    // Initialize Comms
	        pMyDevice->I2cDevAddr      = 0x52;


	    if(Status == VL53L0X_ERROR_NONE)
	        {
	            printf ("Call of VL53L0X_DataInit\n");
	            Status = VL53L0X_DataInit(&MyDevice); // Data initialization
	        }

	        if(Status == VL53L0X_ERROR_NONE)
	        {
	            Status = VL53L0X_GetDeviceInfo(&MyDevice, &DeviceInfo);
	        }
	        if(Status == VL53L0X_ERROR_NONE)
	        {
	            printf("VL53L0X_GetDeviceInfo:\n");
	            printf("Device Name : %s\n", DeviceInfo.Name);
	            printf("Device Type : %s\n", DeviceInfo.Type);
	            printf("Device ID : %s\n", DeviceInfo.ProductId);
	            printf("ProductRevisionMajor : %d\n", DeviceInfo.ProductRevisionMajor);
	            printf("ProductRevisionMinor : %d\n", DeviceInfo.ProductRevisionMinor);

	            if ((DeviceInfo.ProductRevisionMinor != 1) && (DeviceInfo.ProductRevisionMinor != 1)) {
	            	printf("Error expected cut 1.1 but found cut %d.%d\n",
	            			DeviceInfo.ProductRevisionMajor, DeviceInfo.ProductRevisionMinor);
	            	Status = VL53L0X_ERROR_NOT_SUPPORTED;
	            }
	        }


}

Tof_sensor::~Tof_sensor() {
	// TODO Auto-generated destructor stub
}

