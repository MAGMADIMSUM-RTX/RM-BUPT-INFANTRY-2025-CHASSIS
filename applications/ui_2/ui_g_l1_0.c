//
// Created by RM UI Designer
//

#include "ui_g_l1_0.h"

#define FRAME_ID 0
#define GROUP_ID 2
#define START_ID 0
#define OBJ_NUM 2
#define FRAME_OBJ_NUM 2

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_l1_0;
ui_interface_number_t *ui_g_l1_angle = (ui_interface_number_t *)&(ui_g_l1_0.data[0]);
ui_interface_round_t *ui_g_l1_fric_cl = (ui_interface_round_t *)&(ui_g_l1_0.data[1]);

void _ui_init_g_l1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_l1_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_l1_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_l1_0.data[i].figure_name[2] = i + START_ID;
        ui_g_l1_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_l1_0.data[i].operate_tpyel = 0;
    }

    ui_g_l1_angle->figure_tpye = 5;
    ui_g_l1_angle->layer = 1;
    ui_g_l1_angle->font_size = 30;
    ui_g_l1_angle->start_x = 408;
    ui_g_l1_angle->start_y = 794;
    ui_g_l1_angle->color = 1;
    ui_g_l1_angle->number = 12345;
    ui_g_l1_angle->width = 3;

    ui_g_l1_fric_cl->figure_tpye = 2;
    ui_g_l1_fric_cl->layer = 1;
    ui_g_l1_fric_cl->r = 23;
    ui_g_l1_fric_cl->start_x = 271;
    ui_g_l1_fric_cl->start_y = 710;
    ui_g_l1_fric_cl->color = 1;
    ui_g_l1_fric_cl->width = 5;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_l1_0);
    SEND_MESSAGE((uint8_t *) &ui_g_l1_0, sizeof(ui_g_l1_0));
}

void _ui_update_g_l1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_l1_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_l1_0);
    SEND_MESSAGE((uint8_t *) &ui_g_l1_0, sizeof(ui_g_l1_0));
}

void _ui_remove_g_l1_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_l1_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_l1_0);
    SEND_MESSAGE((uint8_t *) &ui_g_l1_0, sizeof(ui_g_l1_0));
}
