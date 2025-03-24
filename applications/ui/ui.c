#include "main.h"
#include "cmsis_os.h"
#include "referee.h"
#include "ui.h"

void ui_task(void *argument){
    while(1){
        // osDelay(500);
        ui_init_g_Ungroup();
        osDelay(100);
        ui_update_g_Ungroup();
        osDelay(500);
        ui_remove_g_Ungroup();
        osDelay(500);
    }
}