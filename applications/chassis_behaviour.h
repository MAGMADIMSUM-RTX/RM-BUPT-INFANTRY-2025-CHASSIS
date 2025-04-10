/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-18 16:41:24
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-17 10:37:32
 * @FilePath: \chassis\applications\chassis_behaviour.h
 * @Description:
 *
 */

#ifndef CHASSIS_BEHAVIOUR_H
#define CHASSIS_BEHAVIOUR_H
#include "struct_typedef.h"

typedef enum
{
    CHASSIS_ZERO_FORCE,                 // chassis will be like no power,底盘无力, 跟没上电那样
    CHASSIS_NO_MOVE,                    // chassis will be stop,底盘保持不动
    CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW, // chassis will follow gimbal, usually in infantry,正常步兵底盘跟随云台
                                        // CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW, // chassis will follow chassis yaw angle, usually in engineer,
                                        //                                      // because chassis does have gyro sensor, its yaw angle is calculed by gyro in gimbal and gimbal motor angle,
                                        //                                      // if you have a gyro sensor in chassis, please updata yaw, pitch, roll angle in "chassis_feedback_update"  function
                                        //                                      // 工程底盘角度控制底盘，由于底盘未有陀螺仪，故而角度是减去云台角度而得到，
                                        //                                      // 如果有底盘陀螺仪请更新底盘的yaw，pitch，roll角度 在chassis_feedback_update函数中
       CHASSIS_NO_FOLLOW_YAW,              // chassis does not follow angle, angle is open-loop,but wheels have closed-loop speed
    //                                      // 底盘不跟随角度，角度是开环的，但轮子是有速度环
    // CHASSIS_OPEN                         // the value of remote control will mulitiply a value, get current value that will be sent to can bus
    //                                      //  遥控器的值乘以比例成电流值 直接发送到can总线上
} chassis_behaviour_e;

enum chassis_spinner_e
{
    CHASSIS_Spinner_Stop = 1,
    CHASSIS_Spinner_Clockwise = 2,
    CHASSIS_Spinner_AntiClockwise = 3,
};

// uint8_t cboard_data[8];
// shift 开启摩擦轮，ctrl关闭摩擦轮
// 鼠标左键按一下发射一个，按住连发，右键按住允许nuc控制发射（nuc可以选择单发或者连发）
// cvb进入不同车的模式
// z开启自瞄
// x关闭自瞄
// 鼠标上下pitch，左右：在badyaw车里是整体左右旋转，在普通车和小陀螺车里是云台独立左右旋转
// 前后控制有两种。es或者ws。
// 云台在一定时间内控制无法到达指定位置，就放弃控制
// enum RobotState_e
// {
//     RobotState_e_Powerless = 0,

//     RobotState_e_GimbalCar = 3,

//     RobotState_e_Spinner_Clockwise = 1,
//     RobotState_e_Spinner_AntiClockwise = 2,
// };

enum RobotState_e
{
    RobotState_e_Powerless = 0,

    RobotState_e_CommonCar = 3,

    RobotState_e_GimbalCar = 1,

    RobotState_e_Spinner = 2,
};

typedef struct
{
//		uint8_t online_flag;
    int16_t channel_0;
    int16_t channel_2;
    int16_t channel_3;
    enum chassis_spinner_e mode;
    uint8_t keyboard;
} can_send_encode_data_s;

// typedef struct
// {
//     int16_t channel_0;
//     int16_t channel_2;
//     int16_t channel_3;
//     enum RobotState_e mode;
//     uint8_t keyboard;
// } can_send_encode_data_s;

typedef union
{
    can_send_encode_data_s data;
    uint8_t data_1[sizeof(can_send_encode_data_s)];
} can_send_data_channel_u;

#endif
