//
// Created by RM UI Designer
//

#include "ui_g_sign_0.h"

#define FRAME_ID 0
#define GROUP_ID 4
#define START_ID 0
#define OBJ_NUM 2
#define FRAME_OBJ_NUM 2

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_sign_0;
ui_interface_rect_t *ui_g_sign_NewRect1 = (ui_interface_rect_t *)&(ui_g_sign_0.data[0]);
ui_interface_rect_t *ui_g_sign_NewRect2 = (ui_interface_rect_t *)&(ui_g_sign_0.data[1]);

void _ui_init_g_sign_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_sign_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_sign_0.data[i].figure_name[2] = i + START_ID;
        ui_g_sign_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_sign_0.data[i].operate_tpyel = 0;
    }

    ui_g_sign_NewRect1->figure_tpye = 1;
    ui_g_sign_NewRect1->layer = 3;
    ui_g_sign_NewRect1->start_x = 1473;
    ui_g_sign_NewRect1->start_y = 764;
    ui_g_sign_NewRect1->color = 2;
    ui_g_sign_NewRect1->width = 1;
    ui_g_sign_NewRect1->end_x = 1493;
    ui_g_sign_NewRect1->end_y = 814;

    ui_g_sign_NewRect2->figure_tpye = 1;
    ui_g_sign_NewRect2->layer = 3;
    ui_g_sign_NewRect2->start_x = 1450;
    ui_g_sign_NewRect2->start_y = 763;
    ui_g_sign_NewRect2->color = 2;
    ui_g_sign_NewRect2->width = 1;
    ui_g_sign_NewRect2->end_x = 1467;
    ui_g_sign_NewRect2->end_y = 795;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_0, sizeof(ui_g_sign_0));
}

void _ui_update_g_sign_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_0, sizeof(ui_g_sign_0));
}

void _ui_remove_g_sign_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_sign_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_sign_0);
    SEND_MESSAGE((uint8_t *) &ui_g_sign_0, sizeof(ui_g_sign_0));
}
