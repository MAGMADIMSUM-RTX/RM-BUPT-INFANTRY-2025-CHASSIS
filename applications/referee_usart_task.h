/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-02-20 19:27:04
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-18 21:53:48
 * @FilePath: \chassis\applications\referee_usart_task.h
 * @Description:
 *
 */
/**
  ****************************(C) COPYRIGHT 2019 DJI****************************
  * @file       referee_usart_task.c/h
  * @brief      RM referee system data solve. RM裁判系统数据处理
  * @note
  * @history
  *  Version    Date            Author          Modification
  *  V1.0.0     Nov-11-2019     RM              1. done
  *
  @verbatim
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************(C) COPYRIGHT 2019 DJI****************************
  */
#ifndef REFEREE_USART_TASK_H
#define REFEREE_USART_TASK_H
#include "main.h"

#define USART_RX_BUF_LENGHT 512
#define REFEREE_FIFO_BUF_LENGTH 1024

/**
 * @brief          referee task
 * @param[in]      pvParameters: NULL
 * @retval         none
 */

/**
 * @brief          裁判系统任务
 * @param[in]      pvParameters: NULL
 * @retval         none
 */

extern void referee_usart_task(void *argument);

#endif
