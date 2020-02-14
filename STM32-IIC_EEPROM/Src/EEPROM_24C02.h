/*
 * EEPROM_24C02.h
 *
 *  Created on: Aug 31, 2019
 *      Author: Weitingee
 */

#ifndef EEPROM_24C02_H_
#define EEPROM_24C02_H_

#include "main.h"

#endif /* EEPROM_24C02_H_ */

void writeEEPROM(I2C_HandleTypeDef *hi2c,uint8_t *writeBuffer,uint8_t ADDR_24LCxx_Write);
void readEEPROM(I2C_HandleTypeDef hi2c,uint8_t *readBuffer,uint8_t ADDR_24LCxx_Read,uint8_t BufferSize);
