#include "struct_typedef.h"
#include "pid.h"
#include "arm_math.h"
#include "CAN_receive.h"
// extern cap_measure_t cap_measure; // capacitor data structure
// extern RC_ctrl_t rc_ctrl;
extern PID_TypeDef Motor_VPID[4];
float initial_total_power = 0;
fp32 power_scale;
// uint8_t cap_state = 0;
/**
 * @brief 底盘功率控制函数，用于控制底盘电机的功率，确保不超过设定的最大功率限制。
 *
 * @param chassis_power_control 指向底盘移动控制结构体的指针，包含电机PID控制和电机测量信息。
 */
void chassis_power_control()
{
    // 定义最大功率限制，单位为瓦特
    uint16_t max_power_limit = 60;
    // 底盘最大可用功率
    fp32 chassis_max_power = 0;
    // 电池输入功率（来自裁判系统）
    float input_power = 0;
    // 每个电机的初始功率，由PID计算得到
    float initial_give_power[4];
    // 所有电机的初始总功率
    // 每个电机缩放后的功率
    fp32 scaled_give_power[4];

    // 底盘当前功率
    fp32 chassis_power = 0.0f;
    // 底盘功率缓冲区
    fp32 chassis_power_buffer = 0.0f;

    // 扭矩系数，用于计算电机功率
    fp32 toque_coefficient = 1.99688994e-6f; // (20/16384)*(0.3)*(187/3591)/9.55
    // 功率计算系数
    fp32 a = 1.23e-07; // k1
    // 功率计算系数
    fp32 k2 = 1.453e-07;
    // 常数项，用于功率计算
    fp32 constant = 4.081f;
    //     // 扭矩系数，用于计算电机功率
    // fp32 toque_coefficient = 1.99688994e-6f; // (20/16384)*(0.3)*(187/3591)/9.55
    // // 功率计算系数
    // fp32 a = 1.23e-07; // k1
    // // 功率计算系数
    // fp32 k2 = 1.453e-07;
    // // 常数项，用于功率计算
    // fp32 constant = 4.081f;

    // // 获取底盘当前功率和功率缓冲区
    // get_chassis_power_and_buffer(&chassis_power, &chassis_power_buffer);
    // // 对功率缓冲区进行PID计算，目标值为30
    // PID_calc(&chassis_power_control->buffer_pid, chassis_power_buffer, 30);
    // // 获取最大功率限制
    // get_chassis_max_power(&max_power_limit);
    // // 计算输入功率，使其在最大功率附近浮动
    // input_power = max_power_limit - chassis_power_control->buffer_pid.out;

    // // 设置电容控制器的输入功率
    // CAN_CMD_CAP(input_power);

    // // 如果遥控器按下E键，设置电容状态为0
    // if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_E)
    // {
    //     cap_state = 0;
    // }
    // // 如果遥控器按下Q键，设置电容状态为1
    // if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_Q)
    // {
    //     cap_state = 1;
    // }

    // // 如果电容电量百分比大于5%
    // if (cap_measure.cap_percent > 5)
    // {
    //     // 如果电容状态为0
    //     if (cap_state == 0)
    //     {
    //         // 底盘最大可用功率稍大于最大功率，避免电容一直处于满电状态，提高能量利用率
    //         chassis_max_power = input_power + 5;
    //     }
    //     else
    //     {
    //         // 底盘最大可用功率增加200
    //         chassis_max_power = input_power + 200;
    //     }
    // }
    // else
    // {
    //     // 电容电量低时，底盘最大可用功率等于输入功率
    // chassis_max_power = input_power;

    // }
    initial_total_power = 0;
    chassis_max_power = max_power_limit;
    // 遍历四个电机，计算每个电机的初始功率和总功率
    for (uint8_t i = 0; i < 4; i++)
    {
        // initial_give_power[i] = chassis_power_control->motor_speed_pid[i].out * toque_coefficient * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm +
        // 						k2 * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm +
        // 						a * chassis_power_control->motor_speed_pid[i].out * chassis_power_control->motor_speed_pid[i].out + constant;

        // 计算每个电机的初始功率
        initial_give_power[i] = Motor_VPID[i].Output * toque_coefficient * get_chassis_motor_measure_point(i)->speed_rpm +
                                k2 * get_chassis_motor_measure_point(i)->speed_rpm * get_chassis_motor_measure_point(i)->speed_rpm +
                                a * Motor_VPID[i].Output * Motor_VPID[i].Output + constant;

        // 如果初始功率为负数，则跳过该电机
        if (initial_give_power[i] < 0)
            continue;
        // 累加初始总功率
        initial_total_power += initial_give_power[i];
    }

    // 如果初始总功率超过底盘最大可用功率
    if (initial_total_power > chassis_max_power)
    {
        // 计算功率缩放因子
        power_scale = chassis_max_power / initial_total_power;
        // 遍历四个电机，计算缩放后的功率
        for (uint8_t i = 0; i < 4; i++)
        {
            // 计算每个电机缩放后的功率
            scaled_give_power[i] = initial_give_power[i] * power_scale;
            // 如果缩放后的功率为负数，则跳过该电机
            if (scaled_give_power[i] < 0)
            {
                continue;
            }

            // 计算二次方程的系数b
            fp32 b = toque_coefficient * get_chassis_motor_measure_point(i)->speed_rpm;
            // 计算二次方程的系数c
            fp32 c = a * get_chassis_motor_measure_point(i)->speed_rpm * get_chassis_motor_measure_point(i)->speed_rpm - scaled_give_power[i] + constant;
            // 计算二次方程的判别式
            fp32 inside = b * b - 4 * a * c;

            // 如果判别式小于0，跳过该电机
            if (inside < 0)
            {
                continue;
            }
            // 根据原始扭矩方向选择计算公式
            else if (Motor_VPID[i].Output > 0)
            {
                // 计算调整后的电机输出值
                fp32 inside_sqrted;
                arm_sqrt_f32(inside, &inside_sqrted);
                fp32 temp = (-b + inside_sqrted) / (2 * a);
                // 限制电机输出值不超过16000
                if (temp > 16000)
                {
                    Motor_VPID[i].Output = 16000;
                }
                else
                    Motor_VPID[i].Output = temp;
            }
            else
            {
                // 计算调整后的电机输出值
                fp32 inside_sqrted;
                arm_sqrt_f32(inside, &inside_sqrted);
                fp32 temp = (-b - inside_sqrted) / (2 * a);
                // 限制电机输出值不低于-16000
                if (temp < -16000)
                {
                    Motor_VPID[i].Output = -16000;
                }
                else
                    Motor_VPID[i].Output = temp;
            }
        }
    }
}
