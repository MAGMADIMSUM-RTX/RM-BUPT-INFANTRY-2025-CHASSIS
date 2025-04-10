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
#include "chassis_behaviour.h"
#include "CAN_receive.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define CHECK_ONLINE_TIMEOUT 50
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

uint8_t chassis_flag = 0;

is_motor_online Motor_online;
uint8_t online_flag = 0;
extern chassis_behaviour_e chassis_behaviour;
/* USER CODE END Variables */
/* Definitions for check_online_ta */
osThreadId_t check_online_taHandle;
const osThreadAttr_t check_online_ta_attributes = {
  .name = "check_online_ta",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
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
  .priority = (osPriority_t) osPriorityRealtime,
};
/* Definitions for uart */
osThreadId_t uartHandle;
const osThreadAttr_t uart_attributes = {
  .name = "uart",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityHigh5,
};
/* Definitions for INS */
osThreadId_t INSHandle;
const osThreadAttr_t INS_attributes = {
  .name = "INS",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for detect */
osThreadId_t detectHandle;
const osThreadAttr_t detect_attributes = {
  .name = "detect",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for referee_usart */
osThreadId_t referee_usartHandle;
const osThreadAttr_t referee_usart_attributes = {
  .name = "referee_usart",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for UI */
osThreadId_t UIHandle;
const osThreadAttr_t UI_attributes = {
  .name = "UI",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void check_online(void *argument);
extern void led_task(void *argument);
extern void chassis_task(void *argument);
extern void uart_task(void *argument);
extern void INS_task(void *argument);
extern void detect_task(void *argument);
extern void referee_usart_task(void *argument);
extern void ui_task(void *argument);

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

  /* creation of uart */
  uartHandle = osThreadNew(uart_task, NULL, &uart_attributes);

  /* creation of INS */
  INSHandle = osThreadNew(INS_task, NULL, &INS_attributes);

  /* creation of detect */
  detectHandle = osThreadNew(detect_task, NULL, &detect_attributes);

  /* creation of referee_usart */
  referee_usartHandle = osThreadNew(referee_usart_task, NULL, &referee_usart_attributes);

  /* creation of UI */
//  UIHandle = osThreadNew(ui_task, NULL, &UI_attributes);

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
__weak void check_online(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN check_online */
  /* Infinite loop */
  // 初始时关闭底盘任务和LED任务，等待确认电机在线
  osThreadTerminate(ChassisHandle);
  osThreadTerminate(LEDHandle);

  while (1)
  {
    for (int i = 0; i < 8; i++)
    {
      uint8_t motor_bit = (1 << i);

      if (online_flag & motor_bit) // 检测到电机在线
      {
        if (Motor_online.motor_online & motor_bit) // 已登记在线，重置计时器
        {
          Motor_online.motor_ticks[i] = 0;
        }
        else // 未登记在线，标记为在线
        {
          Motor_online.motor_online |= motor_bit;
					
					

          if (!chassis_flag &&(
              ((motor_bit == 0x80 && Motor_online.motor_online & 0x0F) ||
               (motor_bit & 0x0F && Motor_online.motor_online & 0x80)))) // 检测到c板在线，启动底盘任务
          {
            chassis_flag = 1;
            LEDHandle = osThreadNew(led_task, NULL, &LED_attributes);
            ChassisHandle = osThreadNew(chassis_task, NULL, &Chassis_attributes);
          }
        }
      }
      else if (Motor_online.motor_online & motor_bit) // 已登记在线但未收到在线信号
      {
        // 增加计时器，超时后标记为离线
        if (++Motor_online.motor_ticks[i] == CHECK_ONLINE_TIMEOUT_COUNT)
        {
          Motor_online.motor_online &= ~motor_bit;
          Motor_online.motor_ticks[i] = 0;

          // 处理c板离线情况
          if (!(Motor_online.motor_online & 0x0F) || !(Motor_online.motor_online & 0x80)) // c板离线或四个轮子都离线
          {
            // 设置底盘为零力矩模式
            chassis_behaviour = CHASSIS_ZERO_FORCE;
            osDelay(200);
            // 发送停止命令
            CAN_cmd_chassis(0, 0, 0, 0);
            // 关闭相关任务
            if (chassis_flag)
            {
              osThreadTerminate(ChassisHandle);
              chassis_flag = 0;
            }
            osThreadTerminate(LEDHandle);
          }
        }
      }
    }
    // 复位在线标志，等待下一轮检测
    online_flag = 0;
    osDelay(CHECK_ONLINE_TASK_DELAY);
  }
  /* USER CODE END check_online */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

