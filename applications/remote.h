#ifndef _REMOTE_H
#define _REMOTE_H
#include "struct_typedef.h"
typedef struct
{
    struct
    {
        int16_t rockerlx; // ��ˮƽ
        int16_t rockerly; // ����ֱ
        int16_t rockerrx; // ��ˮƽ
        int16_t rockerry; // ����ֱ
        int16_t dial;

        uint8_t switchLeft;  // ��࿪��
        uint8_t switchRight; // �Ҳ࿪��
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
