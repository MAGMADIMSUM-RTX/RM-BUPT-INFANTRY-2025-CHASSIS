#include "usart.h"
#include "CAN_receive.h"
#include "main.h"
#include <string.h>
#include "chassis_behaviour.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;
// motor data read
#define get_motor_measure(ptr, data)                               \
  {                                                                \
    (ptr)->last_ecd = (ptr)->ecd;                                  \
    (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);           \
    (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);     \
    (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]); \
    (ptr)->temperate = (data)[6];                                  \
  }
/*
motor data,  0:chassis motor1 3508;1:chassis motor3 3508;2:chassis motor3 3508;3:chassis motor4 3508;
4:yaw gimbal motor 6020;5:pitch gimbal motor 6020;6:trigger motor 2006;
电机数据, 0:底盘电机1 3508电机,  1:底盘电机2 3508电机,2:底盘电机3 3508电机,3:底盘电机4 3508电机;
4:yaw云台电机 6020电机; 5:pitch云台电机 6020电机; 6:拨弹电机 2006电机*/
motor_measure_t motor_chassis[7];

static CAN_TxHeaderTypeDef gimbal_tx_message;
static uint8_t gimbal_can_send_data[8];
static CAN_TxHeaderTypeDef chassis_tx_message;
static uint8_t chassis_can_send_data[8];

int16_t chassis1RawCircle = 0, chassis2RawCircle = 0, chassis3RawCircle = 0, chassis4RawCircle = 0, gimbalyawRawCircle = 0;

CAN_RxHeaderTypeDef cboard_header;

can_send_data_channel_u cboard_data, cboard_data_temp;

extern uint8_t online_flag;

/**
 * @brief          hal库CAN回调函数,接收电机数据
 * @param[in]      hcan:CAN句柄指针
 * @retval         none
 */
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
  CAN_RxHeaderTypeDef rx_header;
  uint8_t rx_data[sizeof(can_send_data_channel_u)];
  HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rx_header, rx_data);

  switch (rx_header.StdId)
  {
  case CAN_3508_M1_ID:
  case CAN_3508_M2_ID:
  case CAN_3508_M3_ID:
  case CAN_3508_M4_ID:
  case CAN_YAW_MOTOR_ID:
  case CAN_PIT_MOTOR_ID:
  case CAN_TRIGGER_MOTOR_ID:
  {
    static uint8_t i = 0;
    // get motor id
    i = rx_header.StdId - CAN_3508_M1_ID;
    online_flag |= (uint8_t)1 << i;

    get_motor_measure(&motor_chassis[i], rx_data);
    break;
  }

  default:
  {
    memcpy(&cboard_data_temp, rx_data, sizeof(can_send_data_channel_u));
    //		if(cboard_data_temp.data.channel_0>=670||cboard_data_temp.data.channel_2>=670||cboard_data_temp.data.channel_3>=670
    //			||cboard_data_temp.data.channel_0<=-670||cboard_data_temp.data.channel_2<=-670||cboard_data_temp.data.channel_3<=-670)
    if (cboard_data_temp.data.mode != 0)
    {
      cboard_header = rx_header;
      //		for(int i=0;i<sizeof(can_send_data_channel_u);i++)
      //			cboard_data.data_1[i]=rx_data[i];
      memcpy(&cboard_data, rx_data, sizeof(can_send_data_channel_u));
      ////		if(cboard_data.data.mode!=RobotState_e_Powerless)
			
			if(cboard_data.data.channel_0)
					online_flag |= (uint8_t)0x80;
      //		printf("%d\n",cboard_data.data.mode);
      break;
    }
  }
  }

  // switch (rx_header.StdId)
  // {
  // case CAN_3508_M1_ID:
  // {
  //   Motor_online.motor_online |= 0x01;
  //   Motor_online.motor_ticks[0] = 0;
  //   break;
  // }
  // case CAN_3508_M2_ID:
  // {
  //   Motor_online.motor_online |= 0x02;
  //   Motor_online.motor_ticks[1] = 0;
  //   break;
  // }
  // case CAN_3508_M3_ID:
  // {
  //   Motor_online.motor_online |= 0x04;
  //   Motor_online.motor_ticks[2] = 0;
  //   break;
  // }
  // case CAN_3508_M4_ID:
  // {
  //   Motor_online.motor_online |= 0x08;
  //   Motor_online.motor_ticks[3] = 0;
  //   break;
  // }
  // case CAN_YAW_MOTOR_ID:
  // {
  //   Motor_online.motor_online |= 0x10;
  //   Motor_online.motor_ticks[4] = 0;
  //   static uint8_t initFlag = 0;
  //   if (initFlag == 0)
  //   {
  //     initFlag = 1;
  //   }
  //   else
  //   {
  //     gimbalyawRawAngle = get_yaw_gimbal_motor_measure_point()->ecd - get_yaw_gimbal_motor_measure_point()->last_ecd;
  //     if (gimbalyawRawAngle > 4096)
  //       gimbalyawRawCircle--;
  //     else if (gimbalyawRawAngle < -4096)
  //       gimbalyawRawCircle++;
  //   }
  //   break;
  // }
  // case CAN_PIT_MOTOR_ID:
  // {
  //   Motor_online.motor_online |= 0x20;
  //   Motor_online.motor_ticks[5] = 0;
  //   break;
  // }
  // case CAN_TRIGGER_MOTOR_ID:
  // {
  //   Motor_online.motor_online |= 0x40;
  //   Motor_online.motor_ticks[6] = 0;
  //   break;
  // }
  // default:
  // {
  //   Motor_online.motor_online |= 0x80;
  //   Motor_online.motor_ticks[7] = 0;
  //   break;
  // }
  // }
}

void CAN_Tansmit(CAN_HandleTypeDef *hcan, uint32_t StdId, uint8_t *pData, uint8_t Length)
{
  uint32_t send_mail_box;
  gimbal_tx_message.StdId = StdId;
  gimbal_tx_message.IDE = CAN_ID_STD;
  gimbal_tx_message.RTR = CAN_RTR_DATA;
  gimbal_tx_message.DLC = Length;
  HAL_CAN_AddTxMessage(hcan, &gimbal_tx_message, pData, &send_mail_box);
}

/**
 * @brief          发送电机控制电??(0x205,0x206,0x207,0x208)
 * @param[in]      yaw: (0x205) 6020电机控制电流, 范围 [-30000,30000]
 * @param[in]      pitch: (0x206) 6020电机控制电流, 范围 [-30000,30000]
 * @param[in]      shoot: (0x207) 2006电机控制电流, 范围 [-10000,10000]
 * @param[in]      rev: (0x208) 保留，电机控制电??
 * @retval         none
 */
void CAN_cmd_gimbal(int16_t yaw, int16_t pitch, int16_t shoot, int16_t rev)
{
  uint32_t send_mail_box;
  gimbal_tx_message.StdId = CAN_GIMBAL_ALL_ID;
  gimbal_tx_message.IDE = CAN_ID_STD;
  gimbal_tx_message.RTR = CAN_RTR_DATA;
  gimbal_tx_message.DLC = 0x08;
  gimbal_can_send_data[0] = (yaw >> 8);
  gimbal_can_send_data[1] = yaw;
  gimbal_can_send_data[2] = (pitch >> 8);
  gimbal_can_send_data[3] = pitch;
  gimbal_can_send_data[4] = (shoot >> 8);
  gimbal_can_send_data[5] = shoot;
  gimbal_can_send_data[6] = (rev >> 8);
  gimbal_can_send_data[7] = rev;
  HAL_CAN_AddTxMessage(&GIMBAL_CAN, &gimbal_tx_message, gimbal_can_send_data, &send_mail_box);
}

/**
 * @brief          发送ID??0x700的CAN??,它会设置3508电机进入快速设置ID
 * @param[in]      none
 * @retval         none
 */
void CAN_cmd_chassis_reset_ID(void)
{
  uint32_t send_mail_box;
  chassis_tx_message.StdId = 0x700;
  chassis_tx_message.IDE = CAN_ID_STD;
  chassis_tx_message.RTR = CAN_RTR_DATA;
  chassis_tx_message.DLC = 0x08;
  chassis_can_send_data[0] = 0;
  chassis_can_send_data[1] = 0;
  chassis_can_send_data[2] = 0;
  chassis_can_send_data[3] = 0;
  chassis_can_send_data[4] = 0;
  chassis_can_send_data[5] = 0;
  chassis_can_send_data[6] = 0;
  chassis_can_send_data[7] = 0;

  HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
 * @brief          发送电机控制电??(0x201,0x202,0x203,0x204)
 * @param[in]      motor1: (0x201) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor2: (0x202) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor3: (0x203) 3508电机控制电流, 范围 [-16384,16384]
 * @param[in]      motor4: (0x204) 3508电机控制电流, 范围 [-16384,16384]
 * @retval         none
 */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
  uint32_t send_mail_box;
  chassis_tx_message.StdId = CAN_CHASSIS_ALL_ID;
  chassis_tx_message.IDE = CAN_ID_STD;
  chassis_tx_message.RTR = CAN_RTR_DATA;
  chassis_tx_message.DLC = 0x08;
  chassis_can_send_data[0] = motor1 >> 8;
  chassis_can_send_data[1] = motor1;
  chassis_can_send_data[2] = motor2 >> 8;
  chassis_can_send_data[3] = motor2;
  chassis_can_send_data[4] = motor3 >> 8;
  chassis_can_send_data[5] = motor3;
  chassis_can_send_data[6] = motor4 >> 8;
  chassis_can_send_data[7] = motor4;

  HAL_CAN_AddTxMessage(&CHASSIS_CAN, &chassis_tx_message, chassis_can_send_data, &send_mail_box);
}

/**
 * @brief          返回yaw 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_yaw_gimbal_motor_measure_point(void)
{
  return &motor_chassis[4];
}

/**
 * @brief          返回pitch 6020电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_pitch_gimbal_motor_measure_point(void)
{
  return &motor_chassis[5];
}

/**
 * @brief          返回拨弹电机 2006电机数据指针
 * @param[in]      none
 * @retval         电机数据指针
 */
const motor_measure_t *get_trigger_motor_measure_point(void)
{
  return &motor_chassis[6];
}

/**
 * @brief          返回底盘电机 3508电机数据指针
 * @param[in]      i: 电机编号,范围[0,3]
 * @retval         电机数据指针
 */
const motor_measure_t *get_chassis_motor_measure_point(uint8_t i)
{
  return &motor_chassis[(i & 0x03)];
}

void pid_abs_limit(float *a, float abs_max)
{
  if (*a > abs_max)
    *a = abs_max;
  if (*a < -abs_max)
    *a = -abs_max;
}

float err;
float err_last;
float total_err;
float pout;
float iout;
float Kp = 8;
float Ki = 0.2;
float out;
float last_out;

float Pid_Caculate(float Mu, float Cu)
{
  err = Cu - Mu; // 误差等于：目标??-测量??
  total_err = err;
  pout = Kp * err;                      // 比例输出
  iout += Ki * err;                     // 积分输出
  pid_abs_limit(&iout, 5000);           // 积分输出限幅
  out = pout + iout;                    // PID计算总输??
  out = out * 0.85f + last_out * 0.15f; // PID输出一阶低通滤??
  pid_abs_limit(&out, 5000);            // PID输出限幅
  err_last = err;

  return out; // 输出PID计算??
}

int16_t motor11;
int16_t motor21;
int16_t motor31;
int16_t motor41;

void CAN(void)
{
  motor11 = Pid_Caculate(motor_chassis[0].speed_rpm, 300);  // 右轮3508电机
  motor21 = Pid_Caculate(motor_chassis[1].speed_rpm, -300); // 左轮3508电机
  motor31 = Pid_Caculate(motor_chassis[2].speed_rpm, -300); // 右轮3508电机
  motor41 = Pid_Caculate(motor_chassis[3].speed_rpm, 300);  // 左轮3508电机
  CAN_cmd_chassis(motor11, motor21, motor31, motor41);
}
