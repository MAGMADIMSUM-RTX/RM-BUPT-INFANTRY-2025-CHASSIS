/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-16 16:06:10
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-28 18:17:26
 * @FilePath: \chassis\applications\uart_task.c
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
extern can_send_data_channel_u cboard_data;
extern ext_power_heat_data_t power_heat_data_t;
extern float initial_total_power;
extern fp32 power_scale;
extern ext_game_robot_state_t robot_state; // ������״̬����
// extern float initial_total_power;
// extern fp32 power_scale;
// extern fp32 scaled_give_power[4];
static char time_info[512];

extern int ui_self_id;

extern uint16_t SPIN_SPEED;
extern uint8_t REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;

void uart_task(void *argument)
{
  TickType_t xLastWakeTime;
  const TickType_t xFrequency = pdMS_TO_TICKS(5);

  static uint8_t chassis_can_send_data[8];
  static CAN_TxHeaderTypeDef chassis_tx_message;
  chassis_tx_message.StdId = 0x88;
  chassis_tx_message.IDE = CAN_ID_STD;
  chassis_tx_message.RTR = CAN_RTR_DATA;
  chassis_tx_message.DLC = 0x08;

  while (1)
  {
    xLastWakeTime = xTaskGetTickCount();

    // printf("%d,%d,%d,%d,%d,%d,%d\n",get_pitch_gimbal_motor_measure_point()->ecd,get_yaw_gimbal_motor_measure_point()->ecd,get_trigger_motor_measure_point()->ecd,get_chassis_motor_measure_point(0)->ecd,get_chassis_motor_measure_point(1)->ecd,get_chassis_motor_measure_point(2)->ecd,get_chassis_motor_measure_point(3)->ecd);

    //    printf("%f,%f,%f,%f,%f,%f,%f\n", gyro[0], gyro[1], gyro[2], accel[0], accel[1], accel[2], temp);

    //		printf("%d,%d,%d,%d,%d,%d,%d,%d,%u,%u,%u,%u\n",classicTargetSpeed[0],classicTargetSpeed[1],classicTargetSpeed[2],classicTargetSpeed[3],classicTargetSpeed_r[0],classicTargetSpeed_r[1],classicTargetSpeed_r[2],classicTargetSpeed_r[3], classicSpeed[0], classicSpeed[1], classicSpeed[2], classicSpeed[3]);

    //		printf("%d\n",cboard_data.data.mode);
    // vTaskGetRunTimeStats(time_info);
    // HAL_UART_Transmit(&huart1, time_info, strlen(time_info), 0x2F);
    // HAL_UART_Transmit(&huart1, "\n", strlen("\n"), 0x2F);
    // printf("%s\n",time_info);
    //
    //    sprintf(judgeMessage, "%d,%f,%f,%f\n", get_robot_id(),power_heat_data_t.chassis_power, power_scale * initial_total_power, initial_total_power);
    // sprintf(judgeMessage, "%d\n",get_yaw_gimbal_motor_measure_point()->ecd);

    //    sprintf(judgeMessage, "%d,%d,%d\n",cboard_data.data.channel_0,cboard_data.data.channel_2,cboard_data.data.channel_3,cboard_data.data.mode);

    // sprintf(judgeMessage, "%d,%d,%d\n",robot_state.robot_level ,SPIN_SPEED,REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO);
    // HAL_UART_Transmit(&huart1, (uint8_t *)judgeMessage, strlen(judgeMessage), 0x2F);

    // HAL_UART_Transmit(&huart1, (uint8_t *)&cboard_data.data.keyboard, 1, 0x2F);
    // HAL_UART_Transmit(&huart1, "\n", 1, 0x2F);
    //		printf("\n");

    //    vTaskDelayUntil(&xLastWakeTime, xFrequency);
    uint32_t send_mail_box;
    chassis_can_send_data[0] =  robot_state.robot_level;
    // chassis_can_send_data[0] = robot_state.robot_level;
    // chassis_can_send_data[1] = motor1;
    // chassis_can_send_data[2] = motor2 >> 8;
    // chassis_can_send_data[3] = motor2;
    // chassis_can_send_data[4] = motor3 >> 8;
    // chassis_can_send_data[5] = motor3;
    // chassis_can_send_data[6] = motor4 >> 8;
    // chassis_can_send_data[7] = motor4;

    HAL_CAN_AddTxMessage(&hcan1, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
    osDelay(10);
  }
}
