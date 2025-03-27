/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-24 22:14:00
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-24 22:16:54
 * @FilePath: \chassis\Src\check_online.c
 * @Description: 100
 * 
 */

uint8_t remote_online_flag = 0;
uint8_t judge_flag = 0;
void check_remote_online(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN check_online */
  /* Infinite loop */
osDelay(1000);
  while (1)
  {
    if(judge_flag==0)
    {
      if(remote_online_flag==0)
      {
        //发送遥控器离线指令
      }
      else
      {
        //发送遥控器在线指令
      }
    }
    osDelay(100);
  }
  /* USER CODE END check_online */
}