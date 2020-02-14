/*
 * ADS1256.c
 *
 *  Created on: Sep 5, 2019
 *      Author: Weitingee
 */


#include "ADS1256.h"



/*
*********************************************************************************************************
*	name: setDIFFChannel
*	function: Write to MUX register - set channel to read from in single-ended mode
*   Bit 7,6,5,4 determine the positive input channel (AINp).
*   Bit 3,2,1,0 determine the negative input channel (AINn). e.g. (0-1, 2,3 - 4,5 - 6,7)
*	parameter:
*	The return value: val
*********************************************************************************************************
*/
void setDIFFChannel(uint8_t positiveCh, uint8_t NegativeCh)
{
	writeByteToReg(REG_MUX, positiveCh <<4 | NegativeCh); //xxxx1000 - AINp = positiveCh, AINn = NegativeCh
}

/*
*********************************************************************************************************
*	name: writeCMD
*	function: Send Standalone commands to register
*	parameter: command
*	The return value: None
*********************************************************************************************************
*/

void writeCMD(uint8_t command)
{
	uint8_t Txbuffer[1];
	Txbuffer[0] = command;
	CS_0();
	HAL_SPI_Transmit(&hspi1, Txbuffer ,1,50);
	CS_1();
}

/*
*********************************************************************************************************
*	name: setDataRate
*	function: sampling rate of collection
*	parameter: pga
*	The return value: None
*********************************************************************************************************
*/
void setDataRate(uint8_t drate)
{
	writeByteToReg(REG_DRATE,drate);
}

/**
*********************************************************************************************************
*	name: writeByteToReg
*	function: read 1 byte from register address registerID.
*	parameter: register ID
*	The return value:
*********************************************************************************************************
*/
void writeByteToReg(uint8_t registerID, uint8_t value)
{
	uint8_t Txbuffer[3];
	Txbuffer[0] = CMD_WREG | registerID;
	Txbuffer[1] = 0x00;
	Txbuffer[2] = value;
	CS_0();
	HAL_SPI_Transmit(&hspi1, Txbuffer ,3,100);
	/*
	send8bit(CMD_WREG | registerID);		//1syt byte: address of the first register to write
	send8bit(0x00);							//2nd byte: number of byte to write = 1.
	send8bit(value);						//3rd byte: value to write to register
	*/
	CS_1();

}
/*
*********************************************************************************************************
*	name: setPGA
*	function: Set gain of amplifier
*	parameter: pga
*	The return value: None
*********************************************************************************************************
*/
void setPGA(uint8_t pga)
{
	writeByteToReg(REG_ADCON,pga);
}
/*
*********************************************************************************************************
*	name: Send8bit
*	function: SPI send data to SPI slave
*	parameter: data
*	The return value: NULL
*********************************************************************************************************
*/
void send8bit(uint8_t data)
{
	HAL_SPI_Transmit(&hspi1, &data ,1,100);
}
/*
*********************************************************************************************************
*	name: waitDRDY
*	function: Wait for DRDY is Low
*	parameter: data
*	The return value: None
*********************************************************************************************************
*/
void waitDRDY(void)
{
	uint32_t i;
		for (i = 0; i < 40000000; i++){
			if (DRDY_IS_LOW()){
				break;
			}
		}
}
/*
*********************************************************************************************************
*	name: readChipID
*	function: Get data from Status register - chipID "check"
*	parameter:
*	The return value: val
*********************************************************************************************************
*/
uint8_t readChipID(void)
{
	waitDRDY();
	volatile uint8_t id = readByteFromReg(REG_STATUS);
	return (id >> 4);
}

/*
*********************************************************************************************************
*	name: receive8bit
*	function: receive data from SPI slave
*	parameter: data
*	The return value: NULL
*********************************************************************************************************
*/
uint8_t receive8bit(void)
{
	/*
	uint8_t TXbuffer[1];
	uint8_t RXbuffer[1];
	TXbuffer[0] = 0xff;

	HAL_SPI_Transmit(&hspi1, TXbuffer ,1,50);
	HAL_SPI_Receive(&hspi1, RXbuffer ,1,50);

	return RXbuffer[0];
	*/
	uint8_t send_data = 0xff;
	uint8_t read = 0;
	HAL_SPI_TransmitReceive(&hspi1,&send_data,&read,1,50);
	return read;



}
/*
*********************************************************************************************************
*	name: readByteFromReg
*	function: read 1 byte from register address registerID.
*	parameter: register ID
*	The return value:
*********************************************************************************************************
*/
uint8_t readByteFromReg(uint8_t registerID)
{
	uint8_t TXbuffer[2];
	TXbuffer[0] = CMD_RREG | registerID;
	TXbuffer[1] = 0x00;
	CS_0();
	HAL_SPI_Transmit(&hspi1, TXbuffer ,2,50);
	delay_us(10);
	uint8_t read = receive8bit();
	CS_1();

	return read;
}
/*
*********************************************************************************************************
*	name: setBuffer
*	function: Set the internal buffer (True-enable), (Fasle-disable)
*	parameter: bool val
*	The return value: val
*********************************************************************************************************
*/
void setBuffer(void)
{
	uint8_t val = 1;
	uint8_t Txbuffer[2];
	Txbuffer[0] = CMD_WREG | REG_STATUS;
	Txbuffer[1] = (0 <<3) | (1 << 2) | (val << 1);

	CS_0();
	HAL_SPI_Transmit(&hspi1, Txbuffer ,2,50);
	//send8bit(CMD_WREG | REG_STATUS);
	//send8bit((0 <<3) | (1 << 2) | (val << 1));
	CS_1();
}
