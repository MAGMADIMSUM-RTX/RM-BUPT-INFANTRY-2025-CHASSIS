/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CHECK_ONLINE_TIMEOUT 100
#define CHECK_ONLINE_TASK_DELAY 5
#define CHECK_ONLINE_TIMEOUT_COUNT (CHECK_ONLINE_TIMEOUT / CHECK_ONLINE_TASK_DELAY)
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
typedef struct
{
  uint8_t motor_online;
  uint8_t motor_ticks[8];
} is_motor_online;

is_motor_online Motor_online;
uint8_t online_flag = 0;
/* USER CODE END Variables */
/* Definitions for check_online_ta */
osThreadId_t check_online_taHandle;
const osThreadAttr_t check_online_ta_attributes = {
  .name = "check_online_ta",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for LED */
osThreadId_t LEDHandle;
const osThreadAttr_t LED_attributes = {
  .name = "LED",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Chassis */
osThreadId_t ChassisHandle;
const osThreadAttr_t Chassis_attributes = {
  .name = "Chassis",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Yaw */
osThreadId_t YawHandle;
const osThreadAttr_t Yaw_attributes = {
  .name = "Yaw",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for uart */
osThreadId_t uartHandle;
const osThreadAttr_t uart_attributes = {
  .name = "uart",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for INS */
osThreadId_t INSHandle;
const osThreadAttr_t INS_attributes = {
  .name = "INS",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void check_online(void *argument);
extern void led_task(void *argument);
extern void chassis_task(void *argument);
extern void yaw_task(void *argument);
extern void uart_task(void *argument);
extern void INS_task(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of check_online_ta */
  check_online_taHandle = osThreadNew(check_online, NULL, &check_online_ta_attributes);

  /* creation of LED */
  LEDHandle = osThreadNew(led_task, NULL, &LED_attributes);

  /* creation of Chassis */
  ChassisHandle = osThreadNew(chassis_task, NULL, &Chassis_attributes);

  /* creation of Yaw */
  YawHandle = osThreadNew(yaw_task, NULL, &Yaw_attributes);

  /* creation of uart */
  uartHandle = osThreadNew(uart_task, NULL, &uart_attributes);

  /* creation of INS */
  INSHandle = osThreadNew(INS_task, NULL, &INS_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_check_online */
/**
  * @brief  Function implementing the check_online_ta thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_check_online */
void check_online(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN check_online */
  /* Infinite loop */
	osThreadTerminate(ChassisHandle);
    osThreadTerminate(LEDHandle);
    osThreadTerminate(YawHandle);
  while(1){

    for (int i = 0; i < 8; i++)
    {
      if (online_flag & (1 << i)) // 检测到在线
      {
        if (Motor_online.motor_online & (1 << i)) // 已登记在线
        {
          Motor_online.motor_ticks[i] = 0;
        }
        else // 未登记在线
        {
          Motor_online.motor_online |= (1 << i);
          // if (i < 4 && (Motor_online.motor_online & 0x0F == 0x0F))
          // {
          //   Chassis_Ctrl_TaHandle = osThreadNew(Chassis_Ctrl, NULL, &Chassis_Ctrl_Ta_attributes);
          //   if (Chassis_Ctrl_TaHandle == NULL)
          //   {

          //     Chassis_Ctrl_TaHandle = osThreadNew(Chassis_Ctrl, NULL, &Chassis_Ctrl_Ta_attributes);
          //   }
          // }
          // else if (i == 4)
          // {
          //   Yaw_Ctrl_TaskHandle = osThreadNew(Yaw_Ctrl, NULL, &Yaw_Ctrl_Task_attributes);
          //   if (Yaw_Ctrl_TaskHandle == NULL)
          //   {

          //     Yaw_Ctrl_TaskHandle = osThreadNew(Yaw_Ctrl, NULL, &Yaw_Ctrl_Task_attributes);
          //   }
          // }
          if (i == 7)
          {
            LEDHandle = osThreadNew(led_task, NULL, &LED_attributes);
            ChassisHandle = osThreadNew(chassis_task, NULL, &Chassis_attributes);
          }
        }
      }
      else if (Motor_online.motor_online & (1 << i))
      {
        if (++Motor_online.motor_ticks[i] == CHECK_ONLINE_TIMEOUT_COUNT)
        {
          Motor_online.motor_online &= ~(1 << i);
          Motor_online.motor_ticks[i] = 0;
          // if (i < 4)
          // {
          //   //todo 锟截闭碉拷锟教匡拷锟斤拷
          // }
          // else if (i == 4)
          // {
          // }
          if (i == 7)
          {
            osThreadTerminate(ChassisHandle);
            osThreadTerminate(LEDHandle);
            CAN_cmd_chassis(0, 0, 0, 0);
          }
        }
      }
    }
    online_flag = 0;
    osDelay(CHECK_ONLINE_TASK_DELAY);
  }
  /* USER CODE END check_online */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

