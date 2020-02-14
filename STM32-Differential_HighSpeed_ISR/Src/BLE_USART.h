/*
 * BLE_USART.h
 *
 *  Created on: Sep 18, 2019
 *      Author: User
 */

#ifndef BLE_USART_H_
#define BLE_USART_H_



#endif /* BLE_USART_H_ */
#define APP_BUFFER_SIZE 128


#define min_(a, b) ((a) < (b)) ? (a) : (b)
#define max_(a, b) ((a) > (b)) ? (a) : (b)
typedef struct
{
	_Bool sendflag;
	//usart transfermit
	char Msg[APP_BUFFER_SIZE];
	unsigned char __attribute__ ((aligned (32))) buffer[APP_BUFFER_SIZE];
	unsigned char __attribute__ ((aligned (32))) Rbuffer[APP_BUFFER_SIZE];
	uint32_t sendTimeout;
	uint32_t bufferSize;

} USART_BLE;
