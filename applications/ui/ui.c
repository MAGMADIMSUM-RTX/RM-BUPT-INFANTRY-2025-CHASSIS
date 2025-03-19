/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-18 19:52:55
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-19 20:25:28
 * @FilePath: \chassis\applications\ui\ui.c
 * @Description:
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "ui.h"
#include "referee.h"

extern int ui_self_id;
void ui_task(void *argument)
{
    osDelay(1000);
    ui_self_id = get_robot_id();
    while (1)
    {
        ui_init_g_Ungroup();
        osDelay(1000);
        ui_update_g_Ungroup();
        osDelay(1000);
        ui_remove_g_Ungroup();
        osDelay(1000);
    }
}
