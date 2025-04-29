/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-25 16:22:21
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-04-29 09:54:37
 * @FilePath: \chassis_bache\applications\chassis_task.h
 * @Description:
 *
 */
#ifndef CHASSIAS_TASK_H
#define CHASSIAS_TASK_H

#include "main.h"
#include "struct_typedef.h"
#include "pid.h"

// typedef struct
// {
//   const RC_ctrl_t *chassis_RC;               //����ʹ�õ�ң����ָ��, the point to remote control
//   const fp32 *chassis_INS_angle;             //the point to the euler angle of gyro sensor.��ȡ�����ǽ������ŷ����ָ��
//   chassis_mode_e chassis_mode;               //state machine. ���̿���״̬��
//   chassis_mode_e last_chassis_mode;          //last state machine.�����ϴο���״̬��
//   chassis_motor_t motor_chassis[4];          //chassis motor data.���̵������
//   pid_type_def motor_speed_pid[4];             //motor speed PID.���̵���ٶ�pid
//   pid_type_def chassis_angle_pid;              //follow angle PID.���̸���Ƕ�pid

//   first_order_filter_type_t chassis_cmd_slow_set_vx;  //use first order filter to slow set-point.ʹ��һ�׵�ͨ�˲������趨ֵ
//   first_order_filter_type_t chassis_cmd_slow_set_vy;  //use first order filter to slow set-point.ʹ��һ�׵�ͨ�˲������趨ֵ

//   fp32 vx;                          //chassis vertical speed, positive means forward,unit m/s. �����ٶ� ǰ������ ǰΪ������λ m/s
//   fp32 vy;                          //chassis horizontal speed, positive means letf,unit m/s.�����ٶ� ���ҷ��� ��Ϊ��  ��λ m/s
//   fp32 wz;                          //chassis rotation speed, positive means counterclockwise,unit rad/s.������ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s
//   fp32 vx_set;                      //chassis set vertical speed,positive means forward,unit m/s.�����趨�ٶ� ǰ������ ǰΪ������λ m/s
//   fp32 vy_set;                      //chassis set horizontal speed,positive means left,unit m/s.�����趨�ٶ� ���ҷ��� ��Ϊ������λ m/s
//   fp32 wz_set;                      //chassis set rotation speed,positive means counterclockwise,unit rad/s.�����趨��ת���ٶȣ���ʱ��Ϊ�� ��λ rad/s
//   fp32 chassis_relative_angle;      //the relative angle between chassis and gimbal.��������̨����ԽǶȣ���λ rad
//   fp32 chassis_relative_angle_set;  //the set relative angle.���������̨���ƽǶ�
//   fp32 chassis_yaw_set;

//   fp32 vx_max_speed;  //max forward speed, unit m/s.ǰ����������ٶ� ��λm/s
//   fp32 vx_min_speed;  //max backward speed, unit m/s.���˷�������ٶ� ��λm/s
//   fp32 vy_max_speed;  //max letf speed, unit m/s.��������ٶ� ��λm/s
//   fp32 vy_min_speed;  //max right speed, unit m/s.�ҷ�������ٶ� ��λm/s
//   fp32 chassis_yaw;   //the yaw angle calculated by gyro sensor and gimbal motor.�����Ǻ���̨������ӵ�yaw�Ƕ�
//   fp32 chassis_pitch; //the pitch angle calculated by gyro sensor and gimbal motor.�����Ǻ���̨������ӵ�pitch�Ƕ�
//   fp32 chassis_roll;  //the roll angle calculated by gyro sensor and gimbal motor.�����Ǻ���̨������ӵ�roll�Ƕ�

// } chassis_move_t;

typedef struct
{
    uint16_t cmd_id;
    float data[3];
} MessageResult;
#endif
