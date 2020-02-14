/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "Delay.h"
#include "Calculate_statistic.h"
#include "arm_const_structs.h"
#include "arm_math.h"
//#include "fft_self.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#define TEST_LENGTH_SAMPLES 8192
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DRDY_IS_LOW() (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3)==0)
#define CS_0()	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
#define CS_1()	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
DMA_HandleTypeDef hdma_i2c1_rx;
DMA_HandleTypeDef hdma_i2c1_tx;

SPI_HandleTypeDef hspi1;
DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

osThreadId ADC_TaskHandle;
osThreadId FFT_TaskHandle;
osThreadId LED_TaskHandle;
osMessageQId adcQueueHandle;
osSemaphoreId adcBinarySemHandle;
osSemaphoreId I2cBinarySemHandle;
/* USER CODE BEGIN PV */

/*
 * I2C private value
 * */
struct I2cCommunication
{
	uint8_t i2cRecive;
	uint8_t i2cSend;
} I2cC;

uint8_t buffer[3];
uint8_t pData[10] = {1,2,3,4,5,6,7,8,9,10};
union FLOAT_BYTE
{
 float f;
 uint8_t byte[sizeof(float)];
}FB;

uint8_t transferbyte[4];
/*
 * Define STM32 Studio charting value
 * */
uint8_t id=0;
float data;
int32_t read = 0;
long TestCount = 0;


/*
 * Define send to ADC message
 * */
uint8_t RDATACsend_data[3] = {0xff,0xff,0xff};
uint8_t Databuffer[3] = {0x00,0x00,0x00};
uint8_t RDATACcmdbuffer[1] = {CMD_RDATAC};
uint8_t SDATACcmduffer[1] = {CMD_SDATAC};


/*
 * Define ADC Info and FFT parameter
 * */
struct ADC_Info{
	uint32_t data_index;
	uint32_t data_length;
	float data_buffer[4096];
	uint8_t data_startFlag;
} ADS1256;


uint32_t fftSize = 4096;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;
uint32_t FFT_COUINT = 0;
uint32_t testIndex = 0;
float32_t maxValue;
float32_t *statisticDataSet;
uint32_t maxtestIndex = 0;
uint32_t mintestIndex = 0;
uint32_t testlength = 0;
/*
 * Define Statistic function
 */
extern struct Statistic_value statistic_value;
/* FreeRTOS private variables;*/
UBaseType_t queueCount;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI1_Init(void);
static void MX_I2C1_Init(void);
void ADC_Thread(void const * argument);
void FFT_Thread(void const * argument);
void LED_Thread(void const * argument);

/* USER CODE BEGIN PFP */
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


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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

//extern float32_t testInput_f32_10khz[TEST_LENGTH_SAMPLES];
float32_t testOutput[TEST_LENGTH_SAMPLES/2];
float *dataRecive[4096];
float *xdatatoSend = ADS1256.data_buffer;
float FFTdata[8192];
float rawData[4096];
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */
  

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_I2C1_Init();
  /* USER CODE BEGIN 2 */

  statisticDataSet = rawData;
  testlength = sizeof(dataRecive)/sizeof(float);

  //Initialize ADS1256 data buffer size
  ADS1256.data_index = 0;
  ADS1256.data_length = 4096;

  //Initialize Frequency range to collection to feature
  FB.f = 1.4567;
  freq_settingValue.freq1 = 0;
  transferbyte[0] = FB.byte[0];
  transferbyte[1] = FB.byte[1];
  transferbyte[2] = FB.byte[2];
  transferbyte[3] = FB.byte[3];
  //Initialize delay systick
  delay_init(122);
  TM_Delay_Init();
  //Reset ADS1256
  writeCMD(CMD_RESET);
  delay_ms(10);
  TM_DelayMicros(1);

  //Initialize ADS1256 parameter (Buffer, PGA, Sampling rate)
  setBuffer();
  setPGA(PGA_GAIN1);
  setDataRate(DRATE_15000);

  //Read chip id
  id = readChipID();

  delay_ms(500);// wait for initialization

  uint8_t  posChannels [4] = {AIN0, AIN2, AIN4, AIN6};
  uint8_t  negChannels [4] = {AIN1, AIN3, AIN5, AIN7};

  // Set differential analog input channel.
  setDIFFChannel(posChannels[1], negChannels[1]);
  delay_us(15);
  writeCMD(CMD_SYNC);    // SYNC command
  delay_us(10);
  writeCMD(CMD_WAKEUP);  // WAKEUP command
  delay_us(15); // min delay: t11 = 4 * 1 / 7,68 Mhz = 0,52 micro sec


  // Set continuous mode.
  waitDRDY();
  CS_0();
  HAL_SPI_Transmit(&hspi1, RDATACcmdbuffer ,1,50);
  delay_ms(25); // min delay: t6 = 50 * 1/7.68 MHz = 6.5 microseconds
  ADS1256.data_startFlag = 1;
  delay_us(1);



  /* USER CODE END 2 */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of adcBinarySem */
  osSemaphoreDef(adcBinarySem);
  adcBinarySemHandle = osSemaphoreCreate(osSemaphore(adcBinarySem), 1);

  /* definition and creation of I2cBinarySem */
  osSemaphoreDef(I2cBinarySem);
  I2cBinarySemHandle = osSemaphoreCreate(osSemaphore(I2cBinarySem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* definition and creation of adcQueue */
  osMessageQDef(adcQueue, 16, long);
  adcQueueHandle = osMessageCreate(osMessageQ(adcQueue), NULL);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of ADC_Task */
  osThreadDef(ADC_Task, ADC_Thread, osPriorityRealtime, 0, 128);
  ADC_TaskHandle = osThreadCreate(osThread(ADC_Task), NULL);

  /* definition and creation of FFT_Task */
  osThreadDef(FFT_Task, FFT_Thread, osPriorityHigh, 0, 128);
  FFT_TaskHandle = osThreadCreate(osThread(FFT_Task), NULL);

  /* definition and creation of LED_Task */
  //osThreadDef(LED_Task, LED_Thread, osPriorityAboveNormal, 0, 128);
  //LED_TaskHandle = osThreadCreate(osThread(LED_Task), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* Start scheduler */
  osKernelStart();
  
  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	//scanSEChannels(channels_SE, num_ch_SE, values_SE);
	//scanDIFFChannels(posChannels, negChannels, num_ch_DIFF, values_DIFF);
	//scanDIFFChannelContinuous(AIN0, AIN1, num_measure_DIFF_CONT, values_DIFF_CONT);
	//delay_ms(1);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 122;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 4;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */
  HAL_I2C_Slave_Receive_IT(&hi2c1, buffer, 2);
  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/** 
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
  /* DMA2_Stream3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13, GPIO_PIN_RESET);

  /*Configure GPIO pin : PA3 */
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA4 */
  GPIO_InitStruct.Pin = GPIO_PIN_4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PD12 PD13 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

}

/* USER CODE BEGIN 4 */

void I2C1_EV_IRQHandler(void)
{
  /* USER CODE BEGIN I2C1_EV_IRQn 0 */

  /* USER CODE END I2C1_EV_IRQn 0 */
    HAL_I2C_EV_IRQHandler(&hi2c1);
  /* USER CODE BEGIN I2C1_EV_IRQn 1 */

    if(buffer[0] == 0x50 && buffer[1] == 0x30)
    {
    	pData[9] = 123;
    	pData[0] = statistic_value.Statistic_max;
    	pData[1] = statistic_value.Statistic_min;
    	pData[2] = statistic_value.Statistic_var;
    	pData[3] = statistic_value.Statistic_rms;
    	pData[4] = statistic_value.Statistic_mean;
    	pData[5] = statistic_value.Statistic_std;
    	pData[6] = statistic_value.Statistic_FreqOvall;
    	pData[7] = statistic_value.Statistic_FreqPeak[0];
    	pData[8] = statistic_value.Statistic_FreqPeak[1];
        if(HAL_I2C_Slave_Transmit_DMA(&hi2c1, pData, 10) == HAL_OK)
    	{

    	}
    }
    else
    {
    	  switch(buffer[0])
    	  {

			  case 0x01:
				  freq_settingValue.freq1 = buffer[1];
				  break;
			  case 0x02:
				  freq_settingValue.freq2 = buffer[1];
				  break;
			  case 0x03:
				  freq_settingValue.freq3 = buffer[1];
				  break;
			  case 0x04:
				  freq_settingValue.freq4 = buffer[1];
				  break;
			  case 0x05:
				  freq_settingValue.freq5 = buffer[1];
				  break;
			  case 0x06:
				  freq_settingValue.freq6 = buffer[1];
				  break;
			  case 0x07:
				  freq_settingValue.freq7 = buffer[1];
				  break;
			  case 0x08:
				  freq_settingValue.freq8 = buffer[1];
				  break;
			  case 0x09:
				  freq_settingValue.freq9 = buffer[1];
				  break;
			  case 0x0A:
				  freq_settingValue.freq10 = buffer[1];
				  break;
			  case 0x0B:
				  freq_settingValue.freq11 = buffer[1];
				  break;
			  case 0x0C:
				  freq_settingValue.freq12 = buffer[1];
				  break;
			  case 0x0D:
				  freq_settingValue.freq13 = buffer[1];
				  break;
			  case 0x0E:
				  freq_settingValue.freq14 = buffer[1];
				  break;
    	  }
    }
    /*
    else if(buffer[0] == 0x01)
    {
    	freq_settingValue.freq1 = buffer[1];
    }
*/



    HAL_I2C_Slave_Receive_IT(&hi2c1, buffer, 2);
  /* USER CODE END I2C1_EV_IRQn 1 */
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin == GPIO_PIN_3 && id == 3 && ADS1256.data_startFlag == 1 && I2cC.i2cRecive == 0)
	{


		    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE because it will get set to pdTRUE inside the interrupt-safe API function if a context switch is required. */

		BaseType_t xHigherPriorityTaskWoken;
		xHigherPriorityTaskWoken = pdFALSE;
		xSemaphoreGiveFromISR(adcBinarySemHandle,&xHigherPriorityTaskWoken);

		if(xHigherPriorityTaskWoken == pdTRUE)
		{
			portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
		}

	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_ADC_Thread */
/**
  * @brief  Function implementing the ADC_Task thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_ADC_Thread */
void ADC_Thread(void const * argument)
{

  /* USER CODE BEGIN 5 */
  const TickType_t xMaxExpectedBlockTime = pdMS_TO_TICKS( 500 );
  //portBASE_TYPE xStatus;
  /* Infinite loop */
  for(;;)
  {
	//vTaskSuspend(NULL);
	 if( xSemaphoreTake( adcBinarySemHandle, xMaxExpectedBlockTime ) == pdPASS && I2cC.i2cRecive == 0){
			HAL_SPI_TransmitReceive_DMA(&hspi1,RDATACsend_data,Databuffer,3);

					// construct 24 bit value
			read  = ((int32_t)Databuffer[0] << 16) & 0x00FF0000;
			read |= ((int32_t)Databuffer[1] << 8);
			read |= Databuffer[2];
			if (read & 0x800000){
				read |= 0xFF000000;

			}

			data = read;
			data = data / 1670000;
			ADS1256.data_buffer[ADS1256.data_index] = data; //plus 2 for FFT using
			ADS1256.data_index++;
			if(ADS1256.data_index == ADS1256.data_length) //divide 2 for FFT real data equal 4096
			{

				/*send data to buffer*/
				BaseType_t xStatus;
				xStatus = xQueueSendToBack(adcQueueHandle, &xdatatoSend , 0);
				queueCount = uxQueueMessagesWaiting(adcQueueHandle);

				if(xStatus == pdPASS)
				{
					vTaskResume(FFT_TaskHandle);
				};
				ADS1256.data_index = 0;
				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_13);
			}

			TM_DelayMicros(8);
	}

  }
  /* USER CODE END 5 */ 
}

/* USER CODE BEGIN Header_FFT_Thread */
/**
* @brief Function implementing the FFT_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_FFT_Thread */
void FFT_Thread(void const * argument)
{
  /* USER CODE BEGIN FFT_Thread */
	//portBASE_TYPE xStatus;

	//const portTickType xTicksToWait = 100 / portTICK_RATE_MS;
  /* Infinite loop */
  for(;;)
  {
	  BaseType_t xStatus;
	  queueCount = uxQueueMessagesWaiting(adcQueueHandle);
	  if(queueCount!=0){
			  xStatus = xQueueReceive(adcQueueHandle, &dataRecive, 100);
			  queueCount = uxQueueMessagesWaiting(adcQueueHandle);

			for(uint32_t i = 0; i<4096; i++)
			{
				//recivedata5 = *(dataRecive[0]+i);
				rawData[i]=*(dataRecive[0]+i);
				FFTdata[i*2] = *(dataRecive[0]+i);
				FFTdata[i*2+1] = 0;
			}

			if(xStatus == pdPASS)
			{

				/* Process the data through the CFFT/CIFFT module */
				arm_cfft_f32(&arm_cfft_sR_f32_len4096, FFTdata, ifftFlag, doBitReverse);

				/* Process the data through the Complex Magnitude Module for
				calculating the magnitude at each bin */
				arm_cmplx_mag_f32(FFTdata, testOutput, fftSize);

				/* Calculates maxValue and returns corresponding BIN value */
				arm_max_f32(testOutput, fftSize, &maxValue, &testIndex);
				FFT_COUINT++;

				maxValue = maxValue/4096;
				for(int i =0; i<2048; i++)
				{
					testOutput[i] = testOutput[i]/4096;
				}

				for(int i =0; i<14; i++)
				{
					Calculate_FreqMax(testOutput,*((&freq_settingValue.freq1)+i), i);
				}




				/*Calcluate math function*/
				arm_max_f32(statisticDataSet, testlength, &statistic_value.Statistic_max, &maxtestIndex);
				arm_min_f32(statisticDataSet, testlength, &statistic_value.Statistic_min, &mintestIndex);
				arm_var_f32(statisticDataSet, testlength, &statistic_value.Statistic_var);
				arm_rms_f32(statisticDataSet, testlength, &statistic_value.Statistic_rms);
				arm_mean_f32(statisticDataSet, testlength, &statistic_value.Statistic_mean);
				arm_std_f32(statisticDataSet, testlength, &statistic_value.Statistic_std);
				arm_rms_f32(testOutput, testlength, &statistic_value.Statistic_FreqOvall);


				HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);
			}

			/*If there is no data in queue, start ads1256 conversion*/

	/*
			if(testIndex !=  refIndex)
			{
			  status = ARM_MATH_TEST_FAILURE;
			}
*/
	  }

	  else{
		 vTaskSuspend(NULL);

	  }
  }
  /* USER CODE END FFT_Thread */
}

/* USER CODE BEGIN Header_LED_Thread */
/**
* @brief Function implementing the LED_Task thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_LED_Thread */
void LED_Thread(void const * argument)
{
  /* USER CODE BEGIN LED_Thread */
  /* Infinite loop */
  for(;;)
  {



  }
  /* USER CODE END LED_Thread */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
