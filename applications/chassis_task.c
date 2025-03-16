#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "CAN_receive.h"
#include "pid.h"
#include "arm_math.h"
#include "chassis_behaviour.h"
// #include "chassis_task.h"
#include "chassis_power_control.h"

#define TASK_GAP 1                           // ??????
#define SPIN_SPEED 12                        // ??????
#define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 4 // ?????????????????????
#define CHASSIS_Acceleration 15              // ????????
#define CHASSIS_MaxSpeed 5000                // ??????????
#define ECD_DEVIATION 2550                   // YAW???????

#define M3508_SPEED_P 18.1
#define M3508_SPEED_I 0.024
#define M3508_SPEED_D 50.73
#define M3508_SPEED_MAXINTERGRAL 10
#define M3508_SPEED_MAXOutput 16384

PID_TypeDef Motor_VPID[4] = {0};
// PID_TypeDef Motor_SPID[4] = {0};

int16_t classicTargetSpeed[4], classicTargetSpeed_r[4], classicSpeed[4];
fp32 chassis_direct;
// extern PID_TypeDef Motor_VPID[4];

extern can_send_data_channel_u cboard_data, last_cboard_data;

typedef enum
{
    remote,
    keyboard,
} cboard_mode;
cboard_mode cboard_mode_switch;

uint8_t cboard_switch;

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

    for (int i = 0; i < 4; i++)
    {
        PID_Init(&Motor_VPID[i], M3508_SPEED_P, M3508_SPEED_I, M3508_SPEED_D, M3508_SPEED_MAXOutput, M3508_SPEED_MAXINTERGRAL, 0.1, 100, 100, 0.02, 0.02, Integral_Limit | OutputFilter);
    }
    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        if (cboard_data.data.keyboard != last_cboard_data.data.keyboard)
        {
            // cboard_data.data.mode = RobotState_e_Powerless;cboard_mode_switch
            cboard_mode_switch = keyboard;
        }
        else if (cboard_data.data.channel_0 != last_cboard_data.data.channel_0 ||
                 cboard_data.data.channel_2 != last_cboard_data.data.channel_2 ||
                 cboard_data.data.channel_3 != last_cboard_data.data.channel_3 ||
                 cboard_data.data.mode != last_cboard_data.data.mode)
        {
            cboard_mode_switch = remote;
        }

        if (cboard_mode_switch == remote)
        {
            if (cboard_data.data.mode == RobotState_e_Powerless)
                chassis_behaviour = CHASSIS_ZERO_FORCE;
            else if (cboard_data.data.mode == RobotState_e_CommonCar)
                chassis_behaviour = CHASSIS_NO_FOLLOW_YAW;
            else if (cboard_data.data.mode == RobotState_e_GimbalCar)
                chassis_behaviour = CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW;
        }
        else if (cboard_mode_switch == keyboard)
        {
            if (cboard_data.data.keyboard & 0x01 == 0)
                chassis_behaviour = CHASSIS_NO_FOLLOW_YAW;
            else
                chassis_behaviour = CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW;
        }

        // ????????????
        // cboard_switch = cboard_data[6];
        // cboard_lx = cboard_data[0] << 8 | cboard_data[1];
        // cboard_ly = cboard_data[2] << 8 | cboard_data[3];

        ChassisGetSpeed(); // ??????????

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
                static int16_t last_cboard_lx, last_cboard_ly;
                if (cboard_mode_switch == remote)
                {
                    last_cboard_lx = cboard_data.data.channel_2;
                    last_cboard_ly = cboard_data.data.channel_3;
                }
                else if (cboard_mode_switch == keyboard)
                {
                    last_cboard_lx =
                        cboard_data.data.keyboard & 0x80 ? 660 : cboard_data.data.keyboard & 0x20 ? -660
                                                                                                  : 0;
                    last_cboard_ly =
                        cboard_data.data.keyboard & 0x40 ? 660 : cboard_data.data.keyboard & 0x10 ? -660
                                                                                                  : 0;
                }
                ChassisGetTargetSpeed(chassis_behaviour, last_cboard_lx, last_cboard_ly); // ?????????????
                ChassisMotorSpeedAccelerationCalculation();                               // ?????????????
            }

            ChassisPIDCalculate();   // PID????
            chassis_power_control(); // ??????????
            CAN_cmd_chassis((int16_t)Motor_VPID[0].Output, (int16_t)Motor_VPID[1].Output, (int16_t)Motor_VPID[2].Output, (int16_t)Motor_VPID[3].Output);
        }
        else
        {
            //            CAN_cmd_chassis(0, 0, 0, 0);
            CAN_cmd_chassis(0, 0, 0, 0);
        }
        last_cboard_data = cboard_data;
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

// void ChassisGetTargetSpeed(enum RobotState_e RobotState, int16_t cboard_lx, int16_t cboard_ly)
void ChassisGetTargetSpeed(chassis_behaviour_e chassis_behaviour, int16_t cboard_lx, int16_t cboard_ly)
{
    static uint32_t time;
    static chassis_behaviour_e last_chassis_behaviour;
    // static enum RobotState_e lastRobotState = RobotState_e_GimbalCar;
    // if (RobotState != lastRobotState)
    //     time = (uint32_t)xLastWakeTime;
    // lastRobotState = RobotState;
    // if (RobotState == RobotState_e_Spinner)

    if (chassis_behaviour != last_chassis_behaviour)
        time = (uint32_t)xLastWakeTime;
    last_chassis_behaviour = chassis_behaviour;
    if (chassis_behaviour == CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW)
    {
        if (time % 2 == 0)
            for (int i = 0; i < 4; i++)
            {
                classicTargetSpeed[i] = SPIN_SPEED;
            }
        else
        {
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
    cordinate_x = (cboard_lx * arm_cos_f32(chassis_direct) - cboard_ly * arm_sin_f32(chassis_direct)) * REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;
    cordinate_y = (cboard_lx * arm_sin_f32(chassis_direct) + cboard_ly * arm_cos_f32(chassis_direct)) * REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;

    classicTargetSpeed[0] += (cordinate_x + cordinate_y);
    classicTargetSpeed[1] += (cordinate_y - cordinate_x);
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
