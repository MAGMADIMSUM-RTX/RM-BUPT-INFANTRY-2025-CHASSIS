//
// Created by RM UI Designer
//

#include "ui_g_line_0.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 0
#define OBJ_NUM 2
#define FRAME_OBJ_NUM 2

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_line_0;
ui_interface_line_t *ui_g_line_line_l = (ui_interface_line_t *)&(ui_g_line_0.data[0]);
ui_interface_line_t *ui_g_line_line_r = (ui_interface_line_t *)&(ui_g_line_0.data[1]);

void _ui_init_g_line_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_line_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_line_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_line_0.data[i].figure_name[2] = i + START_ID;
        ui_g_line_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_line_0.data[i].operate_tpyel = 0;
    }

    ui_g_line_line_l->figure_tpye = 0;
    ui_g_line_line_l->layer = 0;
    ui_g_line_line_l->start_x = 521;
    ui_g_line_line_l->start_y = 105;
    ui_g_line_line_l->end_x = 796;
    ui_g_line_line_l->end_y = 515;
    ui_g_line_line_l->color = 1;
    ui_g_line_line_l->width = 10;

    ui_g_line_line_r->figure_tpye = 0;
    ui_g_line_line_r->layer = 0;
    ui_g_line_line_r->start_x = 1393;
    ui_g_line_line_r->start_y = 82;
    ui_g_line_line_r->end_x = 1124;
    ui_g_line_line_r->end_y = 507;
    ui_g_line_line_r->color = 1;
    ui_g_line_line_r->width = 10;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_line_0);
    SEND_MESSAGE((uint8_t *) &ui_g_line_0, sizeof(ui_g_line_0));
}

void _ui_update_g_line_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_line_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_line_0);
    SEND_MESSAGE((uint8_t *) &ui_g_line_0, sizeof(ui_g_line_0));
}

void _ui_remove_g_line_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_line_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_line_0);
    SEND_MESSAGE((uint8_t *) &ui_g_line_0, sizeof(ui_g_line_0));
}
