#include "main.h"
#include "cmsis_os.h"
#include "referee.h"
#include "ui.h"

extern int ui_self_id;

void ui_task(void *argument){
	osDelay(3000);
	 ui_self_id=get_robot_id();
    while(1){
        ui_init_g_Ungroup();
        osDelay(100);
        ui_update_g_Ungroup();
        osDelay(500);
        ui_remove_g_Ungroup();
        osDelay(500);
    }
}