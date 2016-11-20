


#include "vl53l0x_i2c_platform.h"
#include "vl53l0x_def.h"
#include "vl53l0x_platform_log.h"
#include <Wire.h>
#include <stdint.h>



int VL53L0X_i2c_init() // mja
{

	Wire.begin();
	return 0;
}




extern "C" {

int32_t VL53L0X_write_multi(uint8_t address, uint8_t reg, uint8_t *pdata, uint16_t count)
{
	Wire.beginTransmission(address);
	Wire.write(reg);
	Wire.write(pdata,count);

	Wire.endTransmission();
	return 0;
}

int32_t VL53L0X_read_multi(uint8_t address,  uint8_t index, uint8_t  *pdata, int32_t count)
{
	Wire.beginTransmission(address);
	  Wire.write(index);
	Wire.endTransmission();

	  Wire.requestFrom((int)address, count);

	  while (count-- > 0)
	  {
	    *(pdata++) = Wire.read();
	  }

	  return 0;

}

int32_t VL53L0X_write_byte(uint8_t address,  uint8_t index, uint8_t   data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write(data);

	Wire.endTransmission();
	return 0;

}
int32_t VL53L0X_write_word(uint8_t address,  uint8_t index, uint16_t  data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write((uint8_t*)data,2);

	Wire.endTransmission();
	return 0;

}

int32_t VL53L0X_write_dword(uint8_t address, uint8_t index, uint32_t  data)
{
	Wire.beginTransmission(address);
	Wire.write(index);
	Wire.write((uint8_t*)data,4);

	Wire.endTransmission();
	return 0;
}
int32_t VL53L0X_read_byte(uint8_t address,  uint8_t index, uint8_t  *pdata)
{
	Wire.beginTransmission(address);
	  Wire.write(index);
	Wire.endTransmission();

	  Wire.requestFrom((int)address, 1);

	    *pdata = Wire.read();

	  return 0;

}

int32_t VL53L0X_read_word(uint8_t address,  uint8_t index, uint16_t *pdata)
{
	return VL53L0X_read_multi(address,index,(uint8_t*)pdata, 2);
}

int32_t VL53L0X_read_dword(uint8_t address, uint8_t index, uint32_t *pdata)
{
	return VL53L0X_read_multi(address,index,(uint8_t*)pdata, 4);
}



}

