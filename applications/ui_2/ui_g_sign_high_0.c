//
// Created by RM UI Designer
//

#include "ui_g_sign_high_0.h"

#define FRAME_ID 0
#define GROUP_ID 5
#define START_ID 0
#define OBJ_NUM 1
#define FRAME_OBJ_NUM 1

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_sign_high_0;
ui_interface_rect_t *ui_g_sign_high_NewRect3 = (ui_interface_rect_t *)&(ui_g_sign_high_0.data[0]);

void _ui_init_g_sign_high_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_high_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_sign_high_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_sign_high_0.data[i].figure_name[2] = i + START_ID;
        ui_g_sign_high_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_sign_high_0.data[i].operate_tpyel = 0;
    }

    ui_g_sign_high_NewRect3->figure_tpye = 1;
    ui_g_sign_high_NewRect3->layer = 3;
    ui_g_sign_high_NewRect3->start_x = 1499;
    ui_g_sign_high_NewRect3->start_y = 763;
    ui_g_sign_high_NewRect3->color = 2;
    ui_g_sign_high_NewRect3->width = 1;
    ui_g_sign_high_NewRect3->end_x = 1523;
    ui_g_sign_high_NewRect3->end_y = 841;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_high_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_high_0, sizeof(ui_g_sign_high_0));
}

void _ui_update_g_sign_high_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_high_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_high_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_high_0, sizeof(ui_g_sign_high_0));
}

void _ui_remove_g_sign_high_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_high_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_high_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_high_0, sizeof(ui_g_sign_high_0));
}
