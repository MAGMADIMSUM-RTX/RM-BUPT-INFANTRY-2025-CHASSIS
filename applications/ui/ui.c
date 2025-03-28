/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-26 16:07:47
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-27 19:40:59
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

extern int ui_self_id;
extern ui_interface_arc_t *ui_g_dynamic_spinner;
extern ui_interface_round_t *ui_g_dynamic_fric;
extern ui_interface_line_t *ui_g_dynamic_Line_angle;
extern ui_interface_rect_t *ui_g_dynamic_auto_aim;
extern ui_interface_line_t *ui_g_dynamic_aim_line0;

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
    
    while(1)
    {
        ui_self_id = get_robot_id();
        ui_init_g_Ungroup();
        ui_init_g_dynamic();
        while (1)
        {
            if(cboard_data.data.channel_0 & 0x02) break;

            // auto_aim_update
            if (cboard_data.data.keyboard & 0x02)
            {
                ui_g_dynamic_auto_aim->end_x = 1361;
                ui_g_dynamic_auto_aim->end_y = 833;
                ui_g_dynamic_auto_aim->width = 2;
                ui_g_dynamic_auto_aim->color = 6;
            }
            else
            {
                ui_g_dynamic_auto_aim->end_x = ui_g_dynamic_auto_aim->start_x;
                ui_g_dynamic_auto_aim->end_y = ui_g_dynamic_auto_aim->start_y;
                ui_g_dynamic_auto_aim->color = 8;
                ui_g_dynamic_auto_aim->width = 0;
            }
            if (cboard_data.data.keyboard & 0x08)
            {
                ui_g_dynamic_fric->color = 2;
            }
            else
            {
                ui_g_dynamic_fric->color = 8;
            }
            ui_spinner_update(chassis_direct);
						uint16_t ecd = get_pitch_gimbal_motor_measure_point()->ecd;
            ui_lineangle_update((ecd <4000) ? ecd+8192 :ecd);

            // 4800-5500
            // (get_pitch_gimbal_motor_measure_point()->ecd-4800)/20;
            ui_update_g_dynamic();
            osDelay(50);
        }
        ui_remove_g_Ungroup();
        ui_remove_g_dynamic();
    }
}

void ui_spinner_update(fp32 angle)
{
    ui_g_dynamic_spinner->start_angle = (angle + 2 * PI) * 180.0f / PI + 30.0f;
    ui_g_dynamic_spinner->end_angle = (angle + 2 * PI) * 180.0f / PI - 30.0f;
    ui_update_g_Ungroup();
}

void ui_lineangle_update(uint16_t ecd)
{
    // ecd->700 / 70бу
    int16_t angle = (8176-ecd) / 10;
    float angle_rad = angle * PI / 180.0f;
    ui_g_dynamic_Line_angle->start_x = (int)(960 + 350 * arm_cos_f32(angle_rad));
    ui_g_dynamic_Line_angle->start_y = (int)(540 + 350 * arm_sin_f32(angle_rad));
    ui_g_dynamic_Line_angle->end_x = (int)(960 + 380 * arm_cos_f32(angle_rad));
    ui_g_dynamic_Line_angle->end_y = (int)(540 + 380 * arm_sin_f32(angle_rad));
}
