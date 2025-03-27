#include "referee.h"    // 裁判系统相关函数声明和数据类型定义
#include "string.h"     // 字符串操作相关函数
#include "stdio.h"      // 标准输入输出函数
#include "CRC8_CRC16.h" // CRC校验算法函数
#include "protocol.h"   // 通信协议相关定义

// 通信帧头结构体
frame_header_struct_t referee_receive_header; // 接收数据的帧头
frame_header_struct_t referee_send_header;    // 发送数据的帧头

// 比赛状态数据结构体
ext_game_state_t game_state;         // 比赛状态
ext_game_result_t game_result;       // 比赛结果
ext_game_robot_HP_t game_robot_HP_t; // 机器人血量数据

// 场地事件数据结构体
ext_event_data_t field_event;                                // 场地事件数据
ext_supply_projectile_action_t supply_projectile_action_t;   // 补给站动作数据
ext_supply_projectile_booking_t supply_projectile_booking_t; // 补给站预约数据
ext_referee_warning_t referee_warning_t;                     // 裁判警告数据

// 机器人状态与数据结构体
ext_game_robot_state_t robot_state;                        // 机器人状态数据
ext_power_heat_data_t power_heat_data_t;                   // 功率热量数据
ext_game_robot_pos_t game_robot_pos_t;                     // 机器人位置数据
ext_buff_musk_t buff_musk_t;                               // 机器人增益数据
aerial_robot_energy_t robot_energy_t;                      // 空中机器人能量数据
ext_robot_hurt_t robot_hurt_t;                             // 机器人伤害数据
ext_shoot_data_t shoot_data_t;                             // 射击数据
ext_bullet_remaining_t bullet_remaining_t;                 // 子弹剩余数量
ext_student_interactive_data_t student_interactive_data_t; // 学生机器人间交互数据

/**
 * @brief 初始化裁判系统数据结构体
 * @param void
 * @return void
 * @note 将所有数据结构体内存清零
 */
void init_referee_struct_data(void)
{
    // 初始化通信帧头结构体
    memset(&referee_receive_header, 0, sizeof(frame_header_struct_t));
    memset(&referee_send_header, 0, sizeof(frame_header_struct_t));

    // 初始化比赛状态数据结构体
    memset(&game_state, 0, sizeof(ext_game_state_t));
    memset(&game_result, 0, sizeof(ext_game_result_t));
    memset(&game_robot_HP_t, 0, sizeof(ext_game_robot_HP_t));

    // 初始化场地事件数据结构体
    memset(&field_event, 0, sizeof(ext_event_data_t));
    memset(&supply_projectile_action_t, 0, sizeof(ext_supply_projectile_action_t));
    memset(&supply_projectile_booking_t, 0, sizeof(ext_supply_projectile_booking_t));
    memset(&referee_warning_t, 0, sizeof(ext_referee_warning_t));

    // 初始化机器人状态与数据结构体
    memset(&robot_state, 0, sizeof(ext_game_robot_state_t));
    memset(&power_heat_data_t, 0, sizeof(ext_power_heat_data_t));
    memset(&game_robot_pos_t, 0, sizeof(ext_game_robot_pos_t));
    memset(&buff_musk_t, 0, sizeof(ext_buff_musk_t));
    memset(&robot_energy_t, 0, sizeof(aerial_robot_energy_t));
    memset(&robot_hurt_t, 0, sizeof(ext_robot_hurt_t));
    memset(&shoot_data_t, 0, sizeof(ext_shoot_data_t));
    memset(&bullet_remaining_t, 0, sizeof(ext_bullet_remaining_t));

    // 初始化交互数据结构体
    memset(&student_interactive_data_t, 0, sizeof(ext_student_interactive_data_t));
}

/**
 * @brief 裁判系统数据解析
 * @param frame 接收到的原始数据帧
 * @return void
 * @note 根据命令ID解析不同类型的数据到对应结构体
 */
void referee_data_solve(uint8_t *frame)
{
    uint16_t cmd_id = 0; // 命令ID
    uint8_t index = 0;   // 数据索引

    // 解析帧头
    memcpy(&referee_receive_header, frame, sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    // 解析命令ID
    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);

    // 根据命令ID解析对应数据
    switch (cmd_id)
    {
    case GAME_STATE_CMD_ID: // 比赛状态数据
    {
        memcpy(&game_state, frame + index, sizeof(ext_game_state_t));
    }
    break;
    case GAME_RESULT_CMD_ID: // 比赛结果数据
    {
        memcpy(&game_result, frame + index, sizeof(game_result));
    }
    break;
    case GAME_ROBOT_HP_CMD_ID: // 机器人血量数据
    {
        memcpy(&game_robot_HP_t, frame + index, sizeof(ext_game_robot_HP_t));
    }
    break;

    case FIELD_EVENTS_CMD_ID: // 场地事件数据
    {
        memcpy(&field_event, frame + index, sizeof(field_event));
    }
    break;
    case SUPPLY_PROJECTILE_ACTION_CMD_ID: // 补给站动作数据
    {
        memcpy(&supply_projectile_action_t, frame + index, sizeof(supply_projectile_action_t));
    }
    break;
    case SUPPLY_PROJECTILE_BOOKING_CMD_ID: // 补给站预约数据
    {
        memcpy(&supply_projectile_booking_t, frame + index, sizeof(supply_projectile_booking_t));
    }
    break;
    case REFEREE_WARNING_CMD_ID: // 裁判警告数据
    {
        memcpy(&referee_warning_t, frame + index, sizeof(ext_referee_warning_t));
    }
    break;

    case ROBOT_STATE_CMD_ID: // 机器人状态数据
    {
        memcpy(&robot_state, frame + index, sizeof(robot_state));
    }
    break;
    case POWER_HEAT_DATA_CMD_ID: // 实时功率热量数据
    {
        memcpy(&power_heat_data_t, frame + index, sizeof(power_heat_data_t));
    }
    break;
    case ROBOT_POS_CMD_ID: // 机器人位置数据
    {
        memcpy(&game_robot_pos_t, frame + index, sizeof(game_robot_pos_t));
    }
    break;
    case BUFF_MUSK_CMD_ID: // 机器人增益数据
    {
        memcpy(&buff_musk_t, frame + index, sizeof(buff_musk_t));
    }
    break;
    case AERIAL_ROBOT_ENERGY_CMD_ID: // 空中机器人能量数据
    {
        memcpy(&robot_energy_t, frame + index, sizeof(robot_energy_t));
    }
    break;
    case ROBOT_HURT_CMD_ID: // 伤害状态数据
    {
        memcpy(&robot_hurt_t, frame + index, sizeof(robot_hurt_t));
    }
    break;
    case SHOOT_DATA_CMD_ID: // 实时射击数据
    {
        memcpy(&shoot_data_t, frame + index, sizeof(shoot_data_t));
    }
    break;
    case BULLET_REMAINING_CMD_ID: // 子弹剩余数量
    {
        memcpy(&bullet_remaining_t, frame + index, sizeof(ext_bullet_remaining_t));
    }
    break;
    case STUDENT_INTERACTIVE_DATA_CMD_ID: // 机器人间交互数据
    {
        memcpy(&student_interactive_data_t, frame + index, sizeof(student_interactive_data_t));
    }
    break;
    default: // 未知命令ID
    {
        break;
    }
    }
}

/**
 * @brief 获取底盘功率和缓冲能量
 * @param power 功率指针，用于存储获取的功率值
 * @param buffer 缓冲能量指针，用于存储获取的缓冲能量值
 * @return void
 */
void get_chassis_power_and_buffer(fp32 *power, fp32 *buffer)
{
    *power = power_heat_data_t.chassis_power;         // 当前底盘功率
    *buffer = power_heat_data_t.chassis_power_buffer; // 当前底盘功率缓冲
}

/**
 * @brief 获取机器人ID
 * @param void
 * @return uint8_t 机器人ID
 */
uint8_t get_robot_id(void)
{
    return robot_state.robot_id; // 返回机器人ID
}

/**
 * @brief 获取1号发射机构热量上限和当前热量
 * @param heat0_limit 热量上限指针
 * @param heat0 当前热量指针
 * @return void
 */
void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0)
{
    *heat0_limit = robot_state.shooter_heat0_cooling_limit; // 1号发射机构热量上限
    *heat0 = power_heat_data_t.shooter_heat0;               // 1号发射机构当前热量
}

/**
 * @brief 获取2号发射机构热量上限和当前热量
 * @param heat1_limit 热量上限指针
 * @param heat1 当前热量指针
 * @return void
 */
void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1)
{
    *heat1_limit = robot_state.shooter_heat1_cooling_limit; // 2号发射机构热量上限
    *heat1 = power_heat_data_t.shooter_heat1;               // 2号发射机构当前热量
}

uint8_t get_chassis_power_max()
{
    // uint8_t power_max;
    switch (robot_state.robot_level)
    {
    case 1:
        return 45;

    case 2:
        return 50;

    case 3:
        return 55;

    case 4:
        return 60;

    case 5:
        return 65;

    case 6:
        return 70;

    case 7:
        return 75;

    case 8:
        return 80;

    case 9:
        return 90;

    case 10:
        return 100;

    default:
        return 45;
    }
};