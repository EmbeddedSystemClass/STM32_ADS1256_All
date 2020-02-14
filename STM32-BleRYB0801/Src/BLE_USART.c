/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "math.h"
#include "BLE_USART.h"



/* Private typedef -----------------------------------------------------------*/
extern USART_BLE USARTBLE;	//Wayne0905

/* Private variables ---------------------------------------------------------*/


void BLE_USART(UART_HandleTypeDef *huart, float *sendpData )
{
	if(USARTBLE.sendflag ==1)
	{

		sprintf(USARTBLE.buffer, "%.3f Pa", *sendpData);

		USARTBLE.bufferSize = min(APP_BUFFER_SIZE, strlen(USARTBLE.buffer));
		USARTBLE.sendTimeout = 10 ;
		char a[4];
		a[0] = ("%i \r",255);
		a[1] = ("%i \r",16);
		a[2] = ("%i \r",32);
		a[3] = ("%i \r",48);
		if(HAL_UART_Transmit_DMA(huart, a, 4)==HAL_OK)
		{
			float a = 1;
		}
		/*
		 HAL_UART_Receive(huart , &USARTBLE.Rbuffer, 14, 1000);

		 char C[20];
		 strcpy(C,  USARTBLE.Rbuffer );
		 */
		 //0x1;
	}
}
