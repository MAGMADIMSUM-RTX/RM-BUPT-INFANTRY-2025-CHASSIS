#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "CAN_receive.h"
#include "pid.h"
#include "arm_math.h"
#include "chassis_behaviour.h"
#include "chassis_power_control.h"
#include "referee.h"

// 常量定义
#define TASK_GAP 1 // 任务间隔
// #define SPIN_SPEED 7500                      // 自旋速度
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 8 // 遥控器到底盘速度比例

// #define SPIN_SPEED 8000                      // 自旋速度  //96W					1400
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 16 // 遥控器到底盘速度比例q
// #define SPIN_SPEED 7000                      // 自旋速度  //85W
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 12 // 遥控器到底盘速度比例		1024
// #define SPIN_SPEED 6000                      // 自旋速度  //70W					660
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 12 // 遥控器到底盘速度比例
// #define SPIN_SPEED 5000                      // 自旋速度  //50W         500
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 10 // 遥控器到底盘速度比例
// #define SPIN_SPEED 4000                      // 自旋速度  //45W  20° 400
// #define REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO 8 // 遥控器到底盘速度比例
#define CHASSIS_Acceleration 60 // 底盘加速度
#define CHASSIS_MaxSpeed 8000   // 底盘最大速度 //TODO 观察是否为最大速度
#define ECD_DEVIATION 5856      // YAW轴电机偏差

// PID参数
#define M3508_SPEED_P 18.1
#define M3508_SPEED_I 0.024
#define M3508_SPEED_D 50.73
#define M3508_SPEED_MAXINTERGRAL 10
#define M3508_SPEED_MAXOutput 16384

// 键盘按键位掩码
#define KEY_W 0x80
#define KEY_S 0x20
#define KEY_A 0x40
#define KEY_D 0x10
#define KEY_CTRL 0x01

// 全局变量
PID_TypeDef Motor_VPID[4] = {0};
int16_t classicTargetSpeed[4] = {0}, classicTargetSpeed_r[4] = {0}, classicSpeed[4] = {0};

uint16_t SPIN_SPEED = 4000;
uint8_t REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO = 8;

extern can_send_data_channel_u cboard_data;
can_send_data_channel_u last_cboard_data;
enum chassis_spinner_e chassis_spin_state;
fp32 chassis_direct = 0.0f;

typedef enum
{
    contorller,
    keyboard,
} remote_mode;
remote_mode remote_mode_switch = contorller;

int16_t cordinate_x = 0, cordinate_y = 0;
chassis_behaviour_e chassis_behaviour = CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW;
TickType_t xLastWakeTime = 0;

// 函数声明
void ChassisGetSpeed(void);
void ChassisGetTargetSpeed(chassis_behaviour_e chassis_behaviour, int16_t cboard_lx, int16_t cboard_ly);
void ChassisMotorSpeedAccelerationCalculation(void);
void ChassisPIDCalculate(void);
void UpdateChassisMode(void);

void chassis_task(void *argument)
{
    osDelay(10);
    const TickType_t xFrequency = pdMS_TO_TICKS(TASK_GAP);

    // PID初始化
    for (int i = 0; i < 4; i++)
    {
        PID_Init(&Motor_VPID[i], M3508_SPEED_P, M3508_SPEED_I, M3508_SPEED_D,
                 M3508_SPEED_MAXOutput, M3508_SPEED_MAXINTERGRAL,
                 0.1, 100, 100, 0.02, 0.02,
                 Integral_Limit | OutputFilter);
    }
    last_cboard_data = cboard_data;
    chassis_behaviour = CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW;

    while (1)
    {
        xLastWakeTime = xTaskGetTickCount();

        // 更新控制模式
        UpdateChassisMode();

        // 获取当前速度
        ChassisGetSpeed();

        // 处理不同模式下的底盘控制
        if (chassis_behaviour != CHASSIS_ZERO_FORCE)
        {
            if (chassis_behaviour == CHASSIS_NO_MOVE)
            {
                // 无移动模式，速度目标设为0
                for (int i = 0; i < 4; i++)
                {
                    classicTargetSpeed_r[i] = 0;
                }
            }
            else
            {
                // 处理遥控器或键盘输入
                static int16_t control_x = 0, control_y = 0;
                control_x = 0;
                control_y = 0;

                if (remote_mode_switch == contorller)
                {
                    // 遥控器控制
                    control_x = cboard_data.data.channel_2;
                    control_y = cboard_data.data.channel_3;
                }
                else
                {

                    if (cboard_data.data.keyboard & KEY_D)
                        control_x = 660;
                    if (cboard_data.data.keyboard & KEY_A)
                        control_x = -660;
                    if (cboard_data.data.keyboard & KEY_W)
                        control_y = 660;
                    if (cboard_data.data.keyboard & KEY_S)
                        control_y = -660;
                }

                // 计算目标速度
                ChassisGetTargetSpeed(chassis_behaviour, control_x, control_y);

                // 加速度控制
                ChassisMotorSpeedAccelerationCalculation();
            }

            // PID控制及功率限制
            ChassisPIDCalculate();
            chassis_power_control();

            // 输出到电机
            CAN_cmd_chassis((int16_t)Motor_VPID[0].Output,
                            (int16_t)Motor_VPID[1].Output,
                            (int16_t)Motor_VPID[2].Output,
                            (int16_t)Motor_VPID[3].Output);

            //						CAN_cmd_gimbal(0,0,100,0);
        }
        else
        {
            // 零力矩模式
            CAN_cmd_chassis(0, 0, 0, 0);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

// 更新底盘控制模式
void UpdateChassisMode(void)
{

    SPIN_SPEED = get_spinner_speed();
    REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO = get_chassis_speed_ratio();
    // 检测控制模式切换
    if (cboard_data.data.keyboard != last_cboard_data.data.keyboard)
    {
        remote_mode_switch = keyboard;
    }
    else if (cboard_data.data.channel_0 != last_cboard_data.data.channel_0 ||
             cboard_data.data.channel_2 != last_cboard_data.data.channel_2 ||
             cboard_data.data.channel_3 != last_cboard_data.data.channel_3 ||
             cboard_data.data.mode != last_cboard_data.data.mode)
    {
        remote_mode_switch = contorller;
    }

    // 根据不同控制模式设置底盘行为
    if (remote_mode_switch == contorller)
    {
        chassis_spin_state = cboard_data.data.mode;
    }
    else if (remote_mode_switch == keyboard)
    {
        if ((last_cboard_data.data.keyboard & KEY_CTRL) == 0 && //? 点击shift键切换底盘自旋状态
            (cboard_data.data.keyboard & KEY_CTRL) !=
                (last_cboard_data.data.keyboard & KEY_CTRL))
            if (chassis_spin_state == CHASSIS_Spinner_Stop)
                chassis_spin_state = xTaskGetTickCount() % 2 == 0 ? CHASSIS_Spinner_Clockwise : CHASSIS_Spinner_AntiClockwise;
            else
                chassis_spin_state = CHASSIS_Spinner_Stop;
    }

    // 保存上一次的数据
    last_cboard_data = cboard_data;
}

// 获取电机当前速度
void ChassisGetSpeed(void)
{
    for (int i = 0; i < 4; i++)
    {
        classicSpeed[i] = get_chassis_motor_measure_point(i)->speed_rpm;
    }
}

// 计算目标速度
void ChassisGetTargetSpeed(chassis_behaviour_e chassis_behaviour, int16_t cboard_lx, int16_t cboard_ly)
{

    // static uint32_t time;
    static chassis_behaviour_e last_chassis_behaviour = CHASSIS_ZERO_FORCE;

    // 初始化所有电机目标速度为0
    for (int i = 0; i < 4; i++)
    {
        classicTargetSpeed[i] = 0;
    }

    last_chassis_behaviour = chassis_behaviour;

    // 处理不同行为模式
    if (chassis_behaviour == CHASSIS_INFANTRY_FOLLOW_GIMBAL_YAW)
    {
        static int16_t spin_direction = 0;
        if (chassis_spin_state == CHASSIS_Spinner_Clockwise)
            spin_direction = SPIN_SPEED;
        else if (chassis_spin_state == CHASSIS_Spinner_AntiClockwise)
            spin_direction = SPIN_SPEED;
        // spin_direction = -SPIN_SPEED;
        else
            spin_direction = 0;

        for (int i = 0; i < 4; i++)
        {
            classicTargetSpeed[i] = spin_direction;
        }
    }
    else if (chassis_behaviour == CHASSIS_NO_MOVE)
    {
        for (int i = 0; i < 4; i++)
        {
            classicTargetSpeed[i] = 0;
        }
    }

    // 计算底盘朝向
    //		int16_t piancha =chassis_spin_state==CHASSIS_Spinner_Stop?0: chassis_spin_state==CHASSIS_Spinner_Clockwise?-(get_chassis_power_max()):(get_chassis_power_max());

    static int16_t offsets;

    if (chassis_spin_state == CHASSIS_Spinner_Clockwise)
        offsets = -get_spinner_offsets();
    else if (chassis_spin_state == CHASSIS_Spinner_AntiClockwise)
        offsets = get_spinner_offsets();
    else
        offsets = 0;

    chassis_direct = ((get_yaw_gimbal_motor_measure_point()->ecd - ECD_DEVIATION + offsets) / 8192.0f) * 2 * PI;

    // 计算坐标系下的运动分量
    cordinate_x = (cboard_lx * arm_cos_f32(chassis_direct) - cboard_ly * arm_sin_f32(chassis_direct)) * REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;
    cordinate_y = (cboard_lx * arm_sin_f32(chassis_direct) + cboard_ly * arm_cos_f32(chassis_direct)) * REMOTE_CTRL_TO_CHASSIS_SPEED_RATIO;

    // 根据运动学模型计算四个轮子的速度
    classicTargetSpeed[0] += (cordinate_x + cordinate_y); // 左前轮
    classicTargetSpeed[1] += (cordinate_y - cordinate_x); // 右前轮
    classicTargetSpeed[2] -= (cordinate_x + cordinate_y); // 右后轮
    classicTargetSpeed[3] -= (cordinate_y - cordinate_x); // 左后轮
}

// 电机加速度平滑控制
void ChassisMotorSpeedAccelerationCalculation(void)
{
    for (int i = 0; i < 4; i++)
    {
        int16_t speed_diff = classicTargetSpeed[i] - classicTargetSpeed_r[i];

        if (speed_diff > CHASSIS_Acceleration)
        {
            classicTargetSpeed_r[i] += CHASSIS_Acceleration;
        }
        else if (speed_diff < -CHASSIS_Acceleration)
        {
            classicTargetSpeed_r[i] -= CHASSIS_Acceleration;
        }
        else
        {
            classicTargetSpeed_r[i] = classicTargetSpeed[i];
        }

        // 限制最大速度
        if (classicTargetSpeed_r[i] > CHASSIS_MaxSpeed)
            classicTargetSpeed_r[i] = CHASSIS_MaxSpeed;
        else if (classicTargetSpeed_r[i] < -CHASSIS_MaxSpeed)
            classicTargetSpeed_r[i] = -CHASSIS_MaxSpeed;
    }
}

// PID计算
void ChassisPIDCalculate(void)
{
    for (int i = 0; i < 4; i++)
    {
        PID_Calculate(&Motor_VPID[i], classicSpeed[i], classicTargetSpeed_r[i]);
    }
}
