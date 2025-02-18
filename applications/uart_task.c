/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-16 16:06:10
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-02-17 13:16:24
 * @FilePath: \MDK-ARMd:\Computer\Desktop\Code\RM25\25.1\chassis\applications\debug_uart.c
 * @Description:
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include <string.h>
#include "can.h"
#include "dma.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "struct_typedef.h"
#include "stdio.h"
#include "CAN_receive.h"
#include "bsp_can.h"
#include "pid.h"
#include "remote.h"

// #define TASK_DELAY
extern int classic1TargetSpeed_r, classic2TargetSpeed_r, classic3TargetSpeed_r, classic4TargetSpeed_r;
extern int16_t classic1Speed, classic2Speed, classic3Speed, classic4Speed;
extern int16_t gimbalyawCircle, gimbalyawTargetAngle;
extern int16_t gimbalyawSpeed, gimbalyawTargetSpeed;
extern int16_t gimbalyawRawCircle;
extern uint8_t online_flag;
extern fp32 gyro[3], accel[3], temp;

static char time_info[512];
void uart_task(void *argument)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(10);

  while (1)
  {
    xLastWakeTime = xTaskGetTickCount();

    printf("%f,%f,%f,%f,%f,%f,%f\n", gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], temp);

    // vTaskGetRunTimeStats(time_info);
    // sprintf(txmessage, "%s\n", time_info);
    // 	printf("%s",txmessage);

    //    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(10);
  }
}
