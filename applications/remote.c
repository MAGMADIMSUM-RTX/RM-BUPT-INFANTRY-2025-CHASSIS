/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-01-15 16:19:47
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-01-15 16:20:25
 * @FilePath: \chassis-task2\Src\remote.c
 * @Description:
 *
 */
#include "remote.h"

#define RC_CH_VALUE_OFFSET ((uint16_t)1024)

static uint8_t temp = 0;
RC_Ctl_t remoteCtrl[2] = {0};

void remoteReceive(const uint8_t *sbusBuf)
{
    remoteCtrl[temp].rc.rockerrx = ((sbusBuf[0] | (sbusBuf[1] << 8)) & 0x07ff) - RC_CH_VALUE_OFFSET;
    remoteCtrl[temp].rc.rockerry = (((sbusBuf[1] >> 3) | (sbusBuf[2] << 5)) & 0x07ff) - RC_CH_VALUE_OFFSET;
    remoteCtrl[temp].rc.rockerlx = (((sbusBuf[2] >> 6) | (sbusBuf[3] << 2) | (sbusBuf[4] << 10)) & 0x07ff) - RC_CH_VALUE_OFFSET;
    remoteCtrl[temp].rc.rockerly = ((((sbusBuf[4] >> 1) | (sbusBuf[5] << 7))) & 0x07ff) - RC_CH_VALUE_OFFSET;

    remoteCtrl[temp].rc.dial = (((sbusBuf[16] | (sbusBuf[17] << 8))) & 0x07ff) - RC_CH_VALUE_OFFSET;

    remoteCtrl[temp].rc.switchLeft = ((sbusBuf[5] >> 4) & 0x000C) >> 2;
    remoteCtrl[temp].rc.switchRight = ((sbusBuf[5] >> 4) & 0x0003);

    remoteCtrl[temp].mouse.x = (sbusBuf[6] | (sbusBuf[7] << 8));
    remoteCtrl[temp].mouse.y = (sbusBuf[8] | sbusBuf[9] << 8);
    remoteCtrl[temp].mouse.press_l = sbusBuf[12];
    remoteCtrl[temp].mouse.press_r = sbusBuf[13];

    // temp = temp ? 0 : 1;
}
