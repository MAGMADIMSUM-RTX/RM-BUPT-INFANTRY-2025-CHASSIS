/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-26 16:07:47
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-27 17:37:11
 * @FilePath: \chassis\applications\ui\ui.c
 * @Description:
 *
 */
#include "main.h"
#include "cmsis_os.h"
#include "referee.h"
#include "ui.h"
#include "chassis_behaviour.h"
#include "CAN_receive.h"
#include "arm_math.h"

// #define PI 3.1415926

extern int ui_self_id;
extern ui_interface_arc_t *ui_g_Ungroup_spinner;
extern ui_interface_round_t *ui_g_Ungroup_fric;
extern ui_interface_round_t *ui_g_Ungroup_focus;
extern can_send_data_channel_u cboard_data;
extern fp32 chassis_direct;
int a = 1;

void ui_spinner_update(fp32 angle);
void ui_lineangle_update(uint16_t ecd);

void ui_task(void *argument)
{
    osDelay(1000);

    while (get_robot_id() == 0)
    {
        osDelay(100);
    }

    ui_self_id = get_robot_id();
    ui_init_g_Ungroup();
    while (1)
    {
        // auto_aim_update
        if (cboard_data.data.keyboard & 0x02)
        {
            ui_g_Ungroup_focus->r = 500;
            ui_g_Ungroup_focus->width = 2;
            ui_g_Ungroup_focus->color = 0;
        }
        else
        {
            ui_g_Ungroup_focus->color = 8;
            ui_g_Ungroup_focus->r = 0;
            ui_g_Ungroup_focus->width = 0;
        }
        if (cboard_data.data.keyboard & 0x08)
        {
            ui_g_Ungroup_fric->color = 2;
        }
        else
        {
            ui_g_Ungroup_fric->color = 8;
        }
        ui_spinner_update(chassis_direct);
        ui_lineangle_update(get_pitch_gimbal_motor_measure_point()->ecd);

        // 4800-5500
        // (get_pitch_gimbal_motor_measure_point()->ecd-4800)/20;

        ui_update_g_Ungroup();
        osDelay(2000);
        //        ui_remove_g_Ungroup();
    }
    //    ui_remove_g_Ungroup();
    //    osDelay(500);
}

void ui_spinner_update(fp32 angle)
{
    ui_g_Ungroup_spinner->start_angle = (angle + 2 * PI) * 180.0 / PI + 30;
    ui_g_Ungroup_spinner->start_angle = (angle + 2 * PI) * 180.0 / PI - 30;
    ui_update_g_Ungroup();
}

void ui_lineangle_update(uint16_t ecd)
{
    // ecd->700 / 70бу
    int16_t angle = (ecd - 5150) / 10;
    float angle_rad = angle * PI / 180.0f;
    ui_g_Ungroup_Lineangle->start_x = (int)(960 + 350 * arm_cos_f32(angle_rad));
    ui_g_Ungroup_Lineangle->start_y = (int)(540 + 350 * arm_sin_f32(angle_rad));
    ui_g_Ungroup_Lineangle->end_x = (int)(960 + 380 * arm_cos_f32(angle_rad));
    ui_g_Ungroup_Lineangle->end_y = (int)(540 + 380 * arm_sin_f32(angle_rad));
}
