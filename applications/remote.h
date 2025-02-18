#ifndef _REMOTE_H
#define _REMOTE_H
#include "struct_typedef.h"
typedef struct
{
    struct
    {
        int16_t rockerlx; // 左水平
        int16_t rockerly; // 左竖直
        int16_t rockerrx; // 左水平
        int16_t rockerry; // 左竖直
        int16_t dial;

        uint8_t switchLeft;  // 左侧开关
        uint8_t switchRight; // 右侧开关
    } rc;
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;
        uint8_t press_l;
        uint8_t press_r;
    } mouse;
    struct
    {
        uint16_t v;
    } key;
} RC_Ctl_t;

void remoteReceive(const uint8_t *sbusBuf);

#endif
