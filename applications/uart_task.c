/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-16 16:06:10
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-02-18 13:07:45
 * @FilePath: \MDK-ARMd:\Computer\Desktop\Code\RM25\25.1\chassis\applications\uart_task.c
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
#include "chassis_behaviour.h"
#include "referee.h"

extern fp32 gyro[3], accel[3], temp;
extern int16_t classicTargetSpeed[4], classicTargetSpeed_r[4], classicSpeed[4];
extern can_send_data_channel_u cboard_data;
extern uint8_t judgeMessage[512];

extern int16_t cordinate_x, cordinate_y;
extern ext_power_heat_data_t power_heat_data_t;

static char time_info[512];
void uart_task(void *argument)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(10);

  while (1)
  {
    xLastWakeTime = xTaskGetTickCount();
		
//		printf("%d,%d,%d,%d,%d,%d,%d\n",get_pitch_gimbal_motor_measure_point()->ecd,get_yaw_gimbal_motor_measure_point()->ecd,get_trigger_motor_measure_point()->ecd,get_chassis_motor_measure_point(0)->ecd,get_chassis_motor_measure_point(1)->ecd,get_chassis_motor_measure_point(2)->ecd,get_chassis_motor_measure_point(3)->ecd);
		
//    printf("%f,%f,%f,%f,%f,%f,%f\n", gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], temp);
		
//		printf("%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u,%u\n",classicTargetSpeed[0],classicTargetSpeed[1],classicTargetSpeed[2],classicTargetSpeed[3],classicTargetSpeed_r[0],classicTargetSpeed_r[1],classicTargetSpeed_r[2],classicTargetSpeed_r[3], classicSpeed[0], classicSpeed[1], classicSpeed[2], classicSpeed[3]);

		
//		printf("%d\n",cboard_data.data.mode);
//		vTaskGetRunTimeStats(time_info);
//		printf("%s\n",time_info);
//		
		printf("%f\n",power_heat_data_t.chassis_power);
		
//		HAL_UART_Transmit(&huart1,(uint8_t *)judgeMessage, 512,0x2F);
//		printf("\n");

//    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    osDelay(50);
  }
}
