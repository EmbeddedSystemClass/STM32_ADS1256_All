/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "string.h"
#include "math.h"
#include "BLE_0808iUSART.h"


/* Private typedef -----------------------------------------------------------*/
extern USART_BLE USARTBLE;	//Wayne0905

/* Private variables ---------------------------------------------------------*/


void BLE_USART(UART_HandleTypeDef *huart, float *sendpData )
{
	if(USARTBLE.sendflag ==1)
	{

		//sprintf(USARTBLE.buffer, "%.1f Pa", *sendpData);

		USARTBLE.bufferSize = min(APP_BUFFER_SIZE, strlen(USARTBLE.buffer));
		USARTBLE.sendTimeout = 10 ;
		/*
		if(HAL_UART_Transmit_DMA(huart, &USARTBLE.buffer, USARTBLE.bufferSize )==HAL_OK)
		{
			float a = 1;
		}

		 HAL_UART_Receive(huart , &USARTBLE.Rbuffer, 14, 1000);

		 char C[20];
		 strcpy(C,  USARTBLE.Rbuffer );
		 */
		 //0x1;
	}
}
//HAL_UART_Transmit_DMA(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size)
