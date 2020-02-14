/*
 * EEPROM_24C02.c
 *
 *  Created on: Aug 31, 2019
 *      Author: Weitingee
 */


#include "EEPROM_24C02.h"

void writeEEPROM(I2C_HandleTypeDef *hi2c,uint8_t *writeBuffer,uint8_t ADDR_24LCxx_Write)
{
	  for(uint8_t j=0; j<32; j++)
	  {
		  if(HAL_I2C_Mem_Write(hi2c, ADDR_24LCxx_Write, 8*j, I2C_MEMADD_SIZE_8BIT,writeBuffer+8*j,8, 1000) == HAL_OK)
		  {
			  HAL_Delay(5);
		  }

	  }
}
void readEEPROM(I2C_HandleTypeDef hi2c,uint8_t *readBuffer,uint8_t ADDR_24LCxx_Read,uint8_t BufferSize)
{
	  HAL_I2C_Mem_Read(&hi2c, ADDR_24LCxx_Read, 0, I2C_MEMADD_SIZE_16BIT,readBuffer,BufferSize, 1000);
}
