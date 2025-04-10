/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "can.h"
#include "crc.h"
#include "dma.h"
#include "i2c.h"
#include "rng.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "struct_typedef.h"
#include "stdio.h"
#include "CAN_receive.h"
#include "bsp_can.h"
#include "pid.h"
#include "remote.h"
#include "string.h" // 添加string.h以使用strlen函数
#include "chassis_behaviour.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define BUFFERSIZE 128


#define GVP 40.0f
#define GVI 0.0f
#define GVD 2.0f
// #define GVI 1000.0f
// #define GVD 70.0f
#define GVMAXINTERGRAL 3000
#define GVMAXOutput 30000

#define GSP 0.05f
#define GSI 0.0f
#define GSD 0.0f
#define GSMAXINTERGRAL 12.0f
#define GSMAXOutput 50.0f

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
// PID_TypeDef Gimbal_VPID = {0};
// PID_TypeDef Gimbal_SPID = {0};
char rxmessage[BUFFERSIZE] = {0};
uint8_t judgeMessage[512] = {0};
uint8_t remoteMessage[36] = {0};
uint8_t status = 0;
volatile uint8_t uart_tx_complete = 1; // DMA发送完成标志

extern can_send_data_channel_u cboard_data;
extern RC_Ctl_t remoteCtrl[2];
extern uint8_t online_flag;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
  // HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_11);
  // if (huart == &huart6)
  // {
  //   HAL_UARTEx_ReceiveToIdle_DMA(&huart6, (uint8_t *)rxmessage, BUFFERSIZE);
  //   HAL_UART_Transmit(&huart1, (uint8_t *)rxmessage, BUFFERSIZE, 0x2F);
  // }
  if (huart->Instance == USART3)
  {
		remoteReceive((uint8_t *)remoteMessage);
		cboard_data.data.channel_0=remoteCtrl[0].rc.dial;
		cboard_data.data.channel_2=-remoteCtrl[0].rc.rockerlx;
		cboard_data.data.channel_3=remoteCtrl[0].rc.rockerly;
		switch(remoteCtrl[0].rc.switchRight)
		{
			case 1:{
		cboard_data.data.mode = 2;
			break;
			}
			case 2:{
		cboard_data.data.mode = 3;
			break;
			}
			case 3:{
		cboard_data.data.mode = 1;
			break;
			}
			default:{
						cboard_data.data.mode = 0;

			}
		}
		online_flag |= 0xF0;
    HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)remoteMessage, 36);
  }
  else if (huart->Instance == USART1)
  {
		HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)judgeMessage, 512);
  }
}

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
  MX_ADC1_Init();
  MX_ADC3_Init();
  MX_CAN1_Init();
  MX_CAN2_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_TIM8_Init();
  MX_CRC_Init();
  MX_RNG_Init();
  MX_I2C2_Init();
  MX_I2C3_Init();
  MX_RTC_Init();
  MX_SPI2_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_TIM10_Init();
  MX_USART1_UART_Init();
  MX_USART6_UART_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  // PID_Init(&Gimbal_SPID, GSP, GSI, GSD, GSMAXOutput, GSMAXINTERGRAL, 0.1, 100, 100, 0.02, 0.02, Integral_Limit | OutputFilter);
  // PID_Init(&Gimbal_VPID, GVP, GVI, GVD, GVMAXOutput, GVMAXINTERGRAL, 0.1, 100, 100, 0.02, 0.02, Integral_Limit | OutputFilter);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart1, (uint8_t *)judgeMessage, 512);
  HAL_UARTEx_ReceiveToIdle_DMA(&huart3, (uint8_t *)remoteMessage, 36);
//	HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
//HAL_NVIC_EnableIRQ(USART3_IRQn);

  // HAL_UARTEx_ReceiveToIdle_DMA(&huart6, (uint8_t *)rxmessage, BUFFERSIZE);
  can_filter_init();
  HAL_TIM_Base_Start_IT(&htim5);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in freertos.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//    if(uart_tx_complete)
    {
      uart_tx_complete = 0; // 清除标志，表示正在传输
      // HAL_UART_DMAStop(&huart1);
      HAL_UART_Transmit_DMA(&huart1, (uint8_t *)"Hello!", strlen("Hello!"));
    }
//    HAL_Delay(100);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 6;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
volatile unsigned long ulHighFrequencyTimerTicks;
int fputc(int ch, FILE *f)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0x20);
  return ch;
}

// 添加UART DMA传输完成回调函数
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART1)
  {
    uart_tx_complete = 1; // 设置传输完成标志
  }
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM14 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM14) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */
  if (htim->Instance == TIM5) // TIM5是计算CPU占用率的定时器
  {
    ulHighFrequencyTimerTicks++;
  }
  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
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
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
