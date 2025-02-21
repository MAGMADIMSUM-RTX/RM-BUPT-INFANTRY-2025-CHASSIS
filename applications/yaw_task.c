/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-13 11:02:21
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-02-13 20:52:28
 * @FilePath: \chassis_v0.1\Src\yaw_task.c
 * @Description:
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "stdio.h"
#include "CAN_receive.h"
#include "bsp_can.h"
#include "pid.h"
#include "remote.h"
extern int16_t gimbalyawRawCircle;
extern uint8_t cboard_data[8];
extern PID_TypeDef Gimbal_VPID;
extern PID_TypeDef Gimbal_SPID;
int16_t gimbalyawCircle = 0, gimbalyawTargetAngle;
int16_t gimbalyawSpeed, gimbalyawTargetSpeed;
void yaw_task(void *argument)
{
    osDelay(10);
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(5);
    int16_t cboard_rx = 0;
    uint16_t gimbalyawRawAngle = 0;

    int cnt = 0;
    int speed = 100;
    gimbalyawTargetSpeed = speed;

    while (get_yaw_gimbal_motor_measure_point()->ecd == 0)
        osDelay(2);
    gimbalyawTargetAngle = get_yaw_gimbal_motor_measure_point()->ecd;
    while (1)
    {
        cboard_rx = (int16_t)((int16_t)cboard_data[4] << 8) | cboard_data[5];
        gimbalyawTargetAngle += cboard_rx;
        xLastWakeTime = xTaskGetTickCount();

        gimbalyawSpeed = get_yaw_gimbal_motor_measure_point()->speed_rpm;
        gimbalyawRawAngle = get_yaw_gimbal_motor_measure_point()->ecd;

        gimbalyawCircle = (gimbalyawRawCircle * 1000 + gimbalyawRawAngle / 8.192f);

        // PID_Calculate(&Gimbal_SPID, gimbalyawCircle, gimbalyawTargetAngle);
        // PID_Calculate(&Gimbal_VPID, gimbalyawSpeed, Gimbal_SPID.Output);
        cnt++;
        if (cnt > 500)
        {
            gimbalyawTargetSpeed = -gimbalyawTargetSpeed;
            cnt = 0;
        }
        PID_Calculate(&Gimbal_VPID, gimbalyawSpeed, gimbalyawTargetSpeed);
        CAN_cmd_gimbal(Gimbal_VPID.Output, 0, 0, 0);

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
};
