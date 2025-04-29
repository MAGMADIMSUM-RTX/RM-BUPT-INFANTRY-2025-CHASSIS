/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-26 16:07:47
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-26 16:08:50
 * @FilePath: \ui\ui.c
 * @Description: 
 * 
 */
#include "main.h"
#include "cmsis_os.h"
#include "referee.h"
#include "ui.h"

extern ui_interface_rect_t *ui_g_Ungroup_Rect2;

extern int ui_self_id;

void ui_task(void *argument){
	osDelay(3000);
        ui_init_g_Ungroup();
        osDelay(100);
	ui_self_id=get_robot_id();
    while(1){
    ui_g_Ungroup_Rect2->start_x += 10;
    ui_g_Ungroup_Rect2->end_x += 20;
        ui_update_g_Ungroup();
        osDelay(1000);
    }
		
        ui_remove_g_Ungroup();
        osDelay(500);
}