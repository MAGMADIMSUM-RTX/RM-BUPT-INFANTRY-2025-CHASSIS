#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "BMI088driver.h"

fp32 gyro[3], accel[3], temp;
void INS_task(void *argument){
    while(BMI088_init())
    {
        osDelay(100);
    }
    while(1){
        // BMI088_get_gyro(gyro);
        // BMI088_get_accel(accel);
        // BMI088_get_temp(&temp);
        BMI088_read(gyro, accel, &temp);
        osDelay(100);
    }
}
