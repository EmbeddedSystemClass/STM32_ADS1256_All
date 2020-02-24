/*
 * ADS1256.h
 *
 *  Created on: Sep 5, 2019
 *      Author: Weitingee
 */

#ifndef ADS1256_H_
#define ADS1256_H_

#endif /* ADS1256_H_ */

#include "main.h"
#include "stm32f4xx_hal.h"
#include "Delay.h"
#define DRDY_IS_LOW() (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==0)
#define CS_0()	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
#define CS_1()	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);

extern SPI_HandleTypeDef hspi1;




/*
 * Define ADC Info and FFT parameter
 * */
struct ADC_Info{
	uint32_t data_index;
	uint32_t data_length;
	float data_buffer[4096];
	uint8_t data_startFlag;
} ADS1256;

void waitDRDY(void);
void setBuffer(void);
uint8_t readByteFromReg(uint8_t registerID);
uint8_t receive8bit(void);
uint8_t readChipID(void);
void send8bit(uint8_t data);
void setPGA(uint8_t pga);
void writeByteToReg(uint8_t registerID, uint8_t value);
void setDataRate(uint8_t drate);
void setDIFFChannel(uint8_t positiveCh, uint8_t NegativeCh);
void writeCMD(uint8_t command);
