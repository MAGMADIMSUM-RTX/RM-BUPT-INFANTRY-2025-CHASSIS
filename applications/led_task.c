/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-13 11:59:38
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-02-13 12:04:05
 * @FilePath: \chassis_v0.1\Src\led_ctrl.c
 * @Description:
 *
 */
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#include "struct_typedef.h"
#include "usart.h"
#include <stdio.h>
void led_task(void *argument)
{
    osDelay(10);
    uint8_t status = 0;
    for (;;)
    {
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_10,(GPIO_PinState)( (status >> 0) & (uint8_t)0x01));
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_11, (GPIO_PinState)((status >> 1) &(uint8_t) 0x01));
        HAL_GPIO_WritePin(GPIOH, GPIO_PIN_12, (GPIO_PinState)((status >> 2) & (uint8_t)0x01));
        status++;
        // status += 1;
			
//    HAL_UART_Transmit(&huart6, (uint8_t *)"OK\n", sizeof("OK\n"),10);
        osDelay(500);
    }
    /* USER CODE END LEDCtrl */
}
