#include "referee.h"    // ����ϵͳ��غ����������������Ͷ���
#include "string.h"     // �ַ���������غ���
#include "stdio.h"      // ��׼�����������
#include "CRC8_CRC16.h" // CRCУ���㷨����
#include "protocol.h"   // ͨ��Э����ض���

// ͨ��֡ͷ�ṹ��
frame_header_struct_t referee_receive_header; // �������ݵ�֡ͷ
frame_header_struct_t referee_send_header;    // �������ݵ�֡ͷ

// ����״̬���ݽṹ��
ext_game_state_t game_state;         // ����״̬
ext_game_result_t game_result;       // �������
ext_game_robot_HP_t game_robot_HP_t; // ������Ѫ������

// �����¼����ݽṹ��
ext_event_data_t field_event;                                // �����¼�����
ext_supply_projectile_action_t supply_projectile_action_t;   // ����վ��������
ext_supply_projectile_booking_t supply_projectile_booking_t; // ����վԤԼ����
ext_referee_warning_t referee_warning_t;                     // ���о�������

// ������״̬�����ݽṹ��
ext_game_robot_state_t robot_state;                        // ������״̬����
ext_power_heat_data_t power_heat_data_t;                   // ������������
ext_game_robot_pos_t game_robot_pos_t;                     // ������λ������
ext_buff_musk_t buff_musk_t;                               // ��������������
aerial_robot_energy_t robot_energy_t;                      // ���л�������������
ext_robot_hurt_t robot_hurt_t;                             // �������˺�����
ext_shoot_data_t shoot_data_t;                             // �������
ext_bullet_remaining_t bullet_remaining_t;                 // �ӵ�ʣ������
ext_student_interactive_data_t student_interactive_data_t; // ѧ�������˼佻������

/**
 * @brief ��ʼ������ϵͳ���ݽṹ��
 * @param void
 * @return void
 * @note ���������ݽṹ���ڴ�����
 */
void init_referee_struct_data(void)
{
    // ��ʼ��ͨ��֡ͷ�ṹ��
    memset(&referee_receive_header, 0, sizeof(frame_header_struct_t));
    memset(&referee_send_header, 0, sizeof(frame_header_struct_t));

    // ��ʼ������״̬���ݽṹ��
    memset(&game_state, 0, sizeof(ext_game_state_t));
    memset(&game_result, 0, sizeof(ext_game_result_t));
    memset(&game_robot_HP_t, 0, sizeof(ext_game_robot_HP_t));

    // ��ʼ�������¼����ݽṹ��
    memset(&field_event, 0, sizeof(ext_event_data_t));
    memset(&supply_projectile_action_t, 0, sizeof(ext_supply_projectile_action_t));
    memset(&supply_projectile_booking_t, 0, sizeof(ext_supply_projectile_booking_t));
    memset(&referee_warning_t, 0, sizeof(ext_referee_warning_t));

    // ��ʼ��������״̬�����ݽṹ��
    memset(&robot_state, 0, sizeof(ext_game_robot_state_t));
    memset(&power_heat_data_t, 0, sizeof(ext_power_heat_data_t));
    memset(&game_robot_pos_t, 0, sizeof(ext_game_robot_pos_t));
    memset(&buff_musk_t, 0, sizeof(ext_buff_musk_t));
    memset(&robot_energy_t, 0, sizeof(aerial_robot_energy_t));
    memset(&robot_hurt_t, 0, sizeof(ext_robot_hurt_t));
    memset(&shoot_data_t, 0, sizeof(ext_shoot_data_t));
    memset(&bullet_remaining_t, 0, sizeof(ext_bullet_remaining_t));

    // ��ʼ���������ݽṹ��
    memset(&student_interactive_data_t, 0, sizeof(ext_student_interactive_data_t));
}

/**
 * @brief ����ϵͳ���ݽ���
 * @param frame ���յ���ԭʼ����֡
 * @return void
 * @note ��������ID������ͬ���͵����ݵ���Ӧ�ṹ��
 */
void referee_data_solve(uint8_t *frame)
{
    uint16_t cmd_id = 0; // ����ID
    uint8_t index = 0;   // ��������

    // ����֡ͷ
    memcpy(&referee_receive_header, frame, sizeof(frame_header_struct_t));

    index += sizeof(frame_header_struct_t);

    // ��������ID
    memcpy(&cmd_id, frame + index, sizeof(uint16_t));
    index += sizeof(uint16_t);

    // ��������ID������Ӧ����
    switch (cmd_id)
    {
    case GAME_STATE_CMD_ID: // ����״̬����
    {
        memcpy(&game_state, frame + index, sizeof(ext_game_state_t));
    }
    break;
    case GAME_RESULT_CMD_ID: // �����������
    {
        memcpy(&game_result, frame + index, sizeof(game_result));
    }
    break;
    case GAME_ROBOT_HP_CMD_ID: // ������Ѫ������
    {
        memcpy(&game_robot_HP_t, frame + index, sizeof(ext_game_robot_HP_t));
    }
    break;

    case FIELD_EVENTS_CMD_ID: // �����¼�����
    {
        memcpy(&field_event, frame + index, sizeof(field_event));
    }
    break;
    case SUPPLY_PROJECTILE_ACTION_CMD_ID: // ����վ��������
    {
        memcpy(&supply_projectile_action_t, frame + index, sizeof(supply_projectile_action_t));
    }
    break;
    case SUPPLY_PROJECTILE_BOOKING_CMD_ID: // ����վԤԼ����
    {
        memcpy(&supply_projectile_booking_t, frame + index, sizeof(supply_projectile_booking_t));
    }
    break;
    case REFEREE_WARNING_CMD_ID: // ���о�������
    {
        memcpy(&referee_warning_t, frame + index, sizeof(ext_referee_warning_t));
    }
    break;

    case ROBOT_STATE_CMD_ID: // ������״̬����
    {
        memcpy(&robot_state, frame + index, sizeof(robot_state));
    }
    break;
    case POWER_HEAT_DATA_CMD_ID: // ʵʱ������������
    {
        memcpy(&power_heat_data_t, frame + index, sizeof(power_heat_data_t));
    }
    break;
    case ROBOT_POS_CMD_ID: // ������λ������
    {
        memcpy(&game_robot_pos_t, frame + index, sizeof(game_robot_pos_t));
    }
    break;
    case BUFF_MUSK_CMD_ID: // ��������������
    {
        memcpy(&buff_musk_t, frame + index, sizeof(buff_musk_t));
    }
    break;
    case AERIAL_ROBOT_ENERGY_CMD_ID: // ���л�������������
    {
        memcpy(&robot_energy_t, frame + index, sizeof(robot_energy_t));
    }
    break;
    case ROBOT_HURT_CMD_ID: // �˺�״̬����
    {
        memcpy(&robot_hurt_t, frame + index, sizeof(robot_hurt_t));
    }
    break;
    case SHOOT_DATA_CMD_ID: // ʵʱ�������
    {
        memcpy(&shoot_data_t, frame + index, sizeof(shoot_data_t));
    }
    break;
    case BULLET_REMAINING_CMD_ID: // �ӵ�ʣ������
    {
        memcpy(&bullet_remaining_t, frame + index, sizeof(ext_bullet_remaining_t));
    }
    break;
    case STUDENT_INTERACTIVE_DATA_CMD_ID: // �����˼佻������
    {
        memcpy(&student_interactive_data_t, frame + index, sizeof(student_interactive_data_t));
    }
    break;
    default: // δ֪����ID
    {
        break;
    }
    }
}

/**
 * @brief ��ȡ���̹��ʺͻ�������
 * @param power ����ָ�룬���ڴ洢��ȡ�Ĺ���ֵ
 * @param buffer ��������ָ�룬���ڴ洢��ȡ�Ļ�������ֵ
 * @return void
 */
void get_chassis_power_and_buffer(fp32 *power, fp32 *buffer)
{
    *power = power_heat_data_t.chassis_power;         // ��ǰ���̹���
    *buffer = power_heat_data_t.chassis_power_buffer; // ��ǰ���̹��ʻ���
}

/**
 * @brief ��ȡ������ID
 * @param void
 * @return uint8_t ������ID
 */
uint8_t get_robot_id(void)
{
    return robot_state.robot_id; // ���ػ�����ID
}

/**
 * @brief ��ȡ1�ŷ�������������޺͵�ǰ����
 * @param heat0_limit ��������ָ��
 * @param heat0 ��ǰ����ָ��
 * @return void
 */
void get_shoot_heat0_limit_and_heat0(uint16_t *heat0_limit, uint16_t *heat0)
{
    *heat0_limit = robot_state.shooter_heat0_cooling_limit; // 1�ŷ��������������
    *heat0 = power_heat_data_t.shooter_heat0;               // 1�ŷ��������ǰ����
}

/**
 * @brief ��ȡ2�ŷ�������������޺͵�ǰ����
 * @param heat1_limit ��������ָ��
 * @param heat1 ��ǰ����ָ��
 * @return void
 */
void get_shoot_heat1_limit_and_heat1(uint16_t *heat1_limit, uint16_t *heat1)
{
    *heat1_limit = robot_state.shooter_heat1_cooling_limit; // 2�ŷ��������������
    *heat1 = power_heat_data_t.shooter_heat1;               // 2�ŷ��������ǰ����
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