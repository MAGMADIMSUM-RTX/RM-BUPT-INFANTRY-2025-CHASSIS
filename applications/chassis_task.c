#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "CAN_receive.h"
#include "pid.h"
#include "arm_math.h"
#include "chassis_behaviour.h"

#define TASK_GAP 1                           // 任务间隔
#define SPIN_SPEED 4500                      // 旋转速度
#define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 4 // 遥控器到底盘速度转换比例
#define CHASSIS_Acceleration 15              // 底盘加速度
#define CHASSIS_MaxSpeed 5000                // 底盘最大速度
#define ECD_DEVIATION 2550                     // YAW轴角度偏差

#define M3508_SPEED_P 18.1
#define M3508_SPEED_I 0.024
#define M3508_SPEED_D 50.73
#define M3508_SPEED_MAXINTERGRAL 10
#define M3508_SPEED_MAXOutput 16384

extern motor_measure_t motor_chassis[7];
PID_TypeDef Motor_VPID[4] = {0};
// PID_TypeDef Motor_SPID[4] = {0};

int16_t classicTargetSpeed[4], classicTargetSpeed_r[4], classicSpeed[4];
fp32 chassis_direct;
// extern PID_TypeDef Motor_VPID[4];
extern can_send_data_channel_u cboard_data;
int16_t cordinate_x, cordinate_y;

chassis_behaviour_e chassis_behaviour;
    TickType_t xLastWakeTime;

void ChassisGetSpeed(void);
void ChassisGetTargetSpeed(enum RobotState_e cboard_switch, int16_t cboard_lx, int16_t cboard_ly);
void ChassisMotorSpeedAccelerationCalculation(void);
void ChassisPIDCalculate(void);

void chassis_task(void *argument)
{
    osDelay(10);
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_GAP);

    int16_t cboard_ly, cboard_lx;
    for (int i = 0; i < 4; i++)
    {
        PID_Init(&Motor_VPID[i], M3508_SPEED_P, M3508_SPEED_I, M3508_SPEED_D, M3508_SPEED_MAXOutput, M3508_SPEED_MAXINTERGRAL, 0.1, 100, 100, 0.02, 0.02, Integral_Limit | OutputFilter);
    }
    while (1)
    {
      xLastWakeTime = xTaskGetTickCount();
			
			if(cboard_data.data.mode==RobotState_e_Powerless)
				chassis_behaviour=CHASSIS_ZERO_FORCE;
			else if(cboard_data.data.mode==RobotState_e_CommonCar)
				chassis_behaviour=CHASSIS_NO_FOLLOW_YAW;
			else if(cboard_data.data.mode==RobotState_e_GimbalCar)
				chassis_behaviour=CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW;

        // 提取遥控器数据
        // cboard_switch = cboard_data[6];
        // cboard_lx = cboard_data[0] << 8 | cboard_data[1];
        // cboard_ly = cboard_data[2] << 8 | cboard_data[3];
			
        ChassisGetSpeed(); // 获取底盘速度

        if (chassis_behaviour != CHASSIS_ZERO_FORCE)
        {
            if (chassis_behaviour == CHASSIS_NO_MOVE)
            {
                for (int i = 0; i < 4; i++)
                {
                    classicTargetSpeed_r[i] = 0;
                }
            }
            else
            {
                ChassisGetTargetSpeed(cboard_data.data.mode, cboard_data.data.channel_2, cboard_data.data.channel_3); // 获取底盘目标速度
                ChassisMotorSpeedAccelerationCalculation();                 // 给一个加速度缓冲
            }

            ChassisPIDCalculate(); // PID计算
            CAN_cmd_chassis((int16_t)Motor_VPID[0].Output, (int16_t)Motor_VPID[1].Output, (int16_t)Motor_VPID[2].Output, (int16_t)Motor_VPID[3].Output);
        } else
        {
//            CAN_cmd_chassis(0, 0, 0, 0);
            CAN_cmd_chassis(0, 0, 0, 0);
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void ChassisGetSpeed(void)
{
    for (int i = 0; i < 4; i++)
    {
        classicSpeed[i] = get_chassis_motor_measure_point(i)->speed_rpm;
    }
}

void ChassisGetTargetSpeed(enum RobotState_e RobotState, int16_t cboard_lx, int16_t cboard_ly)
{
	static enum RobotState_e lastRobotState=RobotState_e_GimbalCar;
	static uint32_t time;
	if(RobotState!=lastRobotState)
		time=(uint32_t)xLastWakeTime;
	lastRobotState = RobotState;
    if (RobotState == RobotState_e_Spinner)
    {
			if(time%2==0)
        for (int i = 0; i < 4; i++)
        {
            classicTargetSpeed[i] = SPIN_SPEED;
        }
			else{
        for (int i = 0; i < 4; i++)
        {
            classicTargetSpeed[i] = -SPIN_SPEED;
        }
			}
    }
    else
    {
        for (int i = 0; i < 4; i++)
        {
            classicTargetSpeed[i] = 0;
        }
    }

    chassis_direct = ((get_yaw_gimbal_motor_measure_point()->ecd - ECD_DEVIATION) / 8192.0f) * 2 * PI;
//    chassis_direct = get_yaw_gimbal_motor_measure_point()->ecd * 51471.8540364f;
    cordinate_x = (cboard_lx * arm_cos_f32(chassis_direct) - cboard_ly * arm_sin_f32(chassis_direct))* REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;
    cordinate_y = (cboard_lx * arm_sin_f32(chassis_direct) + cboard_ly * arm_cos_f32(chassis_direct))* REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;
    
    classicTargetSpeed[0] += (cordinate_x + cordinate_y) ;
    classicTargetSpeed[1] += (cordinate_y - cordinate_x) ;
    classicTargetSpeed[2] -= (cordinate_x + cordinate_y);
    classicTargetSpeed[3] -= (cordinate_y - cordinate_x);
}

void ChassisMotorSpeedAccelerationCalculation(void)
{
    for (int i = 0; i < 4; i++)
    {
        if (classicTargetSpeed[i] - classicTargetSpeed_r[i] > CHASSIS_Acceleration)
        {
            classicTargetSpeed_r[i] += CHASSIS_Acceleration;
        }
        else if (classicTargetSpeed[i] - classicTargetSpeed_r[i] < -CHASSIS_Acceleration)
        {
            classicTargetSpeed_r[i] -= CHASSIS_Acceleration;
        }
        else
        {
            classicTargetSpeed_r[i] = classicTargetSpeed[i];
        }
    }
}

void ChassisPIDCalculate(void)
{
    for (int i = 0; i < 4; i++)
    {
        PID_Calculate(&Motor_VPID[i], classicSpeed[i], classicTargetSpeed_r[i]);
    }
}
