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
 * @brief ���̹��ʿ��ƺ��������ڿ��Ƶ��̵���Ĺ��ʣ�ȷ���������趨����������ơ�
 *
 * @param chassis_power_control ָ������ƶ����ƽṹ���ָ�룬�������PID���ƺ͵��������Ϣ��
 */
void chassis_power_control()
{
    // ������������ƣ���λΪ����
    uint16_t max_power_limit = 60;
    // ���������ù���
    fp32 chassis_max_power = 0;
    // ������빦�ʣ����Բ���ϵͳ��
    float input_power = 0;
    // ÿ������ĳ�ʼ���ʣ���PID����õ�
    float initial_give_power[4];
    // ���е���ĳ�ʼ�ܹ���
    // ÿ��������ź�Ĺ���
    fp32 scaled_give_power[4];

    // ���̵�ǰ����
    fp32 chassis_power = 0.0f;
    // ���̹��ʻ�����
    fp32 chassis_power_buffer = 0.0f;

    // Ť��ϵ�������ڼ���������
    fp32 toque_coefficient = 1.99688994e-6f; // (20/16384)*(0.3)*(187/3591)/9.55
    // ���ʼ���ϵ��
    fp32 a = 1.23e-07; // k1
    // ���ʼ���ϵ��
    fp32 k2 = 1.453e-07;
    // ��������ڹ��ʼ���
    fp32 constant = 4.081f;
    //     // Ť��ϵ�������ڼ���������
    // fp32 toque_coefficient = 1.99688994e-6f; // (20/16384)*(0.3)*(187/3591)/9.55
    // // ���ʼ���ϵ��
    // fp32 a = 1.23e-07; // k1
    // // ���ʼ���ϵ��
    // fp32 k2 = 1.453e-07;
    // // ��������ڹ��ʼ���
    // fp32 constant = 4.081f;

    // // ��ȡ���̵�ǰ���ʺ͹��ʻ�����
    // get_chassis_power_and_buffer(&chassis_power, &chassis_power_buffer);
    // // �Թ��ʻ���������PID���㣬Ŀ��ֵΪ30
    // PID_calc(&chassis_power_control->buffer_pid, chassis_power_buffer, 30);
    // // ��ȡ���������
    // get_chassis_max_power(&max_power_limit);
    // // �������빦�ʣ�ʹ��������ʸ�������
    // input_power = max_power_limit - chassis_power_control->buffer_pid.out;

    // // ���õ��ݿ����������빦��
    // CAN_CMD_CAP(input_power);

    // // ���ң��������E�������õ���״̬Ϊ0
    // if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_E)
    // {
    //     cap_state = 0;
    // }
    // // ���ң��������Q�������õ���״̬Ϊ1
    // if (rc_ctrl.key.v & KEY_PRESSED_OFFSET_Q)
    // {
    //     cap_state = 1;
    // }

    // // ������ݵ����ٷֱȴ���5%
    // if (cap_measure.cap_percent > 5)
    // {
    //     // �������״̬Ϊ0
    //     if (cap_state == 0)
    //     {
    //         // ���������ù����Դ�������ʣ��������һֱ��������״̬���������������
    //         chassis_max_power = input_power + 5;
    //     }
    //     else
    //     {
    //         // ���������ù�������200
    //         chassis_max_power = input_power + 200;
    //     }
    // }
    // else
    // {
    //     // ���ݵ�����ʱ�����������ù��ʵ������빦��
    // chassis_max_power = input_power;

    // }
    initial_total_power = 0;
    chassis_max_power = max_power_limit;
    // �����ĸ����������ÿ������ĳ�ʼ���ʺ��ܹ���
    for (uint8_t i = 0; i < 4; i++)
    {
        // initial_give_power[i] = chassis_power_control->motor_speed_pid[i].out * toque_coefficient * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm +
        // 						k2 * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm * chassis_power_control->motor_chassis[i].chassis_motor_measure->speed_rpm +
        // 						a * chassis_power_control->motor_speed_pid[i].out * chassis_power_control->motor_speed_pid[i].out + constant;

        // ����ÿ������ĳ�ʼ����
        initial_give_power[i] = Motor_VPID[i].Output * toque_coefficient * get_chassis_motor_measure_point(i)->speed_rpm +
                                k2 * get_chassis_motor_measure_point(i)->speed_rpm * get_chassis_motor_measure_point(i)->speed_rpm +
                                a * Motor_VPID[i].Output * Motor_VPID[i].Output + constant;

        // �����ʼ����Ϊ�������������õ��
        if (initial_give_power[i] < 0)
            continue;
        // �ۼӳ�ʼ�ܹ���
        initial_total_power += initial_give_power[i];
    }

    // �����ʼ�ܹ��ʳ������������ù���
    if (initial_total_power > chassis_max_power)
    {
        // ���㹦����������
        power_scale = chassis_max_power / initial_total_power;
        // �����ĸ�������������ź�Ĺ���
        for (uint8_t i = 0; i < 4; i++)
        {
            // ����ÿ��������ź�Ĺ���
            scaled_give_power[i] = initial_give_power[i] * power_scale;
            // ������ź�Ĺ���Ϊ�������������õ��
            if (scaled_give_power[i] < 0)
            {
                continue;
            }

            // ������η��̵�ϵ��b
            fp32 b = toque_coefficient * get_chassis_motor_measure_point(i)->speed_rpm;
            // ������η��̵�ϵ��c
            fp32 c = a * get_chassis_motor_measure_point(i)->speed_rpm * get_chassis_motor_measure_point(i)->speed_rpm - scaled_give_power[i] + constant;
            // ������η��̵��б�ʽ
            fp32 inside = b * b - 4 * a * c;

            // ����б�ʽС��0�������õ��
            if (inside < 0)
            {
                continue;
            }
            // ����ԭʼŤ�ط���ѡ����㹫ʽ
            else if (Motor_VPID[i].Output > 0)
            {
                // ���������ĵ�����ֵ
                fp32 inside_sqrted;
                arm_sqrt_f32(inside, &inside_sqrted);
                fp32 temp = (-b + inside_sqrted) / (2 * a);
                // ���Ƶ�����ֵ������16000
                if (temp > 16000)
                {
                    Motor_VPID[i].Output = 16000;
                }
                else
                    Motor_VPID[i].Output = temp;
            }
            else
            {
                // ���������ĵ�����ֵ
                fp32 inside_sqrted;
                arm_sqrt_f32(inside, &inside_sqrted);
                fp32 temp = (-b - inside_sqrted) / (2 * a);
                // ���Ƶ�����ֵ������-16000
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
