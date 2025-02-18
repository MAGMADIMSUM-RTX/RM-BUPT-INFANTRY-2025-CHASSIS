#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include <stdio.h>
#include "struct_typedef.h"
#include "stdio.h"
#include "CAN_receive.h"
#include "bsp_can.h"
#include "pid.h"
#include "remote.h"
#include "arm_math.h"

#define TASK_GAP 1 //任务间隔
#define CHASSIS_Acceleration 15 //底盘加速度
#define CHASSIS_MaxSpeed 5000 //底盘最大速度
#define ECD_DEVIATION 0 //YAW轴角度偏差

int16_t classic1TargetSpeed, classic2TargetSpeed, classic3TargetSpeed, classic4TargetSpeed;
int16_t classic1TargetSpeed_r = 0, classic2TargetSpeed_r = 0, classic3TargetSpeed_r = 0, classic4TargetSpeed_r = 0;
int16_t classic1Speed, classic2Speed, classic3Speed, classic4Speed;
fp32 chassis_direct;
extern PID_TypeDef Motor_VPID[4];
extern uint8_t cboard_data[8];

void ChassisMotorSpeedAccelerationCalculation(void);

void chassis_task(void *argument)
{
  osDelay(10);
  const TickType_t xFrequency = pdMS_TO_TICKS(TASK_GAP);
  int p = 500;
  TickType_t xLastWakeTime;
  uint8_t cboard_switch;
  int16_t cboard_ly, cboard_lx;
  int16_t cordinate_x, cordinate_y;
  while(1)
  {
    xLastWakeTime = xTaskGetTickCount();

    classic1Speed = get_chassis_motor_measure_point(0)->speed_rpm;
    classic2Speed = get_chassis_motor_measure_point(1)->speed_rpm;
    classic3Speed = get_chassis_motor_measure_point(2)->speed_rpm;
    classic4Speed = get_chassis_motor_measure_point(3)->speed_rpm;

    cboard_switch = cboard_data[6];
    cboard_lx = cboard_data[0] << 8 | cboard_data[1];
    cboard_ly = cboard_data[2] << 8 | cboard_data[3];

    if (cboard_switch == 1)
    {
      classic1TargetSpeed = classic2TargetSpeed = classic3TargetSpeed = classic4TargetSpeed = p;
    }
    else if (cboard_switch == 2)
    {
      classic1TargetSpeed = classic2TargetSpeed = classic3TargetSpeed = classic4TargetSpeed = -p;
    }
    else
    {
			classic1TargetSpeed = classic2TargetSpeed = classic3TargetSpeed = classic4TargetSpeed = 0;
    }      
    
    chassis_direct=get_yaw_gimbal_motor_measure_point()->ecd/8192.0f*2*PI;
    cordinate_x = cboard_lx * arm_cos_f32(chassis_direct) - cboard_ly * arm_sin_f32(chassis_direct);
    cordinate_y = cboard_lx * arm_sin_f32(chassis_direct) + cboard_ly * arm_cos_f32(chassis_direct);

    classic1TargetSpeed += (cordinate_x + cordinate_y) * 2;
    classic2TargetSpeed += (cordinate_y - cordinate_x) * 2;
    classic3TargetSpeed -= (cordinate_x + cordinate_y) * 2;
    classic4TargetSpeed -= (cordinate_y - cordinate_x) * 2;

		ChassisMotorSpeedAccelerationCalculation();
    
    PID_Calculate(&Motor_VPID[0], classic1Speed, classic1TargetSpeed_r);
    PID_Calculate(&Motor_VPID[1], classic2Speed, classic2TargetSpeed_r);
    PID_Calculate(&Motor_VPID[2], classic3Speed, classic3TargetSpeed_r);
    PID_Calculate(&Motor_VPID[3], classic4Speed, classic4TargetSpeed_r);
    CAN_cmd_chassis((int16_t)Motor_VPID[0].Output, (int16_t)Motor_VPID[1].Output, (int16_t)Motor_VPID[2].Output, (int16_t)Motor_VPID[3].Output);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

void ChassisMotorSpeedAccelerationCalculation(void){
if (classic1TargetSpeed - classic1TargetSpeed_r > CHASSIS_Acceleration)
    {
      classic1TargetSpeed_r += CHASSIS_Acceleration;
    }
    else if (classic1TargetSpeed - classic1TargetSpeed_r < -CHASSIS_Acceleration)
    {
      classic1TargetSpeed_r -= CHASSIS_Acceleration;
    }
    else
    {
      classic1TargetSpeed_r = classic1TargetSpeed;
    }

    if (classic2TargetSpeed - classic2TargetSpeed_r > CHASSIS_Acceleration)
    {
      classic2TargetSpeed_r += CHASSIS_Acceleration;
    }
    else if (classic2TargetSpeed - classic2TargetSpeed_r < -CHASSIS_Acceleration)
    {
      classic2TargetSpeed_r -= CHASSIS_Acceleration;
    }
    else
    {
      classic2TargetSpeed_r = classic2TargetSpeed;
    }

    if (classic3TargetSpeed - classic3TargetSpeed_r > CHASSIS_Acceleration)
    {
      classic3TargetSpeed_r += CHASSIS_Acceleration;
    }
    else if (classic3TargetSpeed - classic3TargetSpeed_r < -CHASSIS_Acceleration)
    {
      classic3TargetSpeed_r -= CHASSIS_Acceleration;
    }
    else
    {
      classic3TargetSpeed_r = classic3TargetSpeed;
    }

    if (classic4TargetSpeed - classic4TargetSpeed_r > CHASSIS_Acceleration)
    {
      classic4TargetSpeed_r += CHASSIS_Acceleration;
    }
    else if (classic4TargetSpeed - classic4TargetSpeed_r < -CHASSIS_Acceleration)
    {
      classic4TargetSpeed_r -= CHASSIS_Acceleration;
    }
    else
    {
      classic4TargetSpeed_r = classic4TargetSpeed;
    }
}