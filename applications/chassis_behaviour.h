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
    CHASSIS_ZERO_FORCE,                 // chassis will be like no power,��������, ��û�ϵ�����
    CHASSIS_NO_MOVE,                    // chassis will be stop,���̱��ֲ���
    CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW, // chassis will follow gimbal, usually in infantry,�����������̸�����̨
                                        // CHASSIS_ENGINEER_FOLLOW_CHASSIS_YAW, // chassis will follow chassis yaw angle, usually in engineer,
                                        //                                      // because chassis does have gyro sensor, its yaw angle is calculed by gyro in gimbal and gimbal motor angle,
                                        //                                      // if you have a gyro sensor in chassis, please updata yaw, pitch, roll angle in "chassis_feedback_update"  function
                                        //                                      // ���̵��̽Ƕȿ��Ƶ��̣����ڵ���δ�������ǣ��ʶ��Ƕ��Ǽ�ȥ��̨�Ƕȶ��õ���
                                        //                                      // ����е�������������µ��̵�yaw��pitch��roll�Ƕ� ��chassis_feedback_update������
       CHASSIS_NO_FOLLOW_YAW,              // chassis does not follow angle, angle is open-loop,but wheels have closed-loop speed
    //                                      // ���̲�����Ƕȣ��Ƕ��ǿ����ģ������������ٶȻ�
    // CHASSIS_OPEN                         // the value of remote control will mulitiply a value, get current value that will be sent to can bus
    //                                      //  ң������ֵ���Ա����ɵ���ֵ ֱ�ӷ��͵�can������
} chassis_behaviour_e;

enum chassis_spinner_e
{
    CHASSIS_Spinner_Stop = 1,
    CHASSIS_Spinner_Clockwise = 2,
    CHASSIS_Spinner_AntiClockwise = 3,
};

// uint8_t cboard_data[8];
// shift ����Ħ���֣�ctrl�ر�Ħ����
// ��������һ�·���һ������ס�������Ҽ���ס����nuc���Ʒ��䣨nuc����ѡ�񵥷�����������
// cvb���벻ͬ����ģʽ
// z��������
// x�ر�����
// �������pitch�����ң���badyaw����������������ת������ͨ����С���ݳ�������̨����������ת
// ǰ����������֡�es����ws��
// ��̨��һ��ʱ���ڿ����޷�����ָ��λ�ã��ͷ�������
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
    uint8_t switch_left;
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
