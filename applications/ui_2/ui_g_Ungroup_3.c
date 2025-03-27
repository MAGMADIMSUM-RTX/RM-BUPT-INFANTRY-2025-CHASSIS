//
// Created by RM UI Designer
//

#include "ui_g_Ungroup_3.h"

#define FRAME_ID 0
#define GROUP_ID 1
#define START_ID 3
#define OBJ_NUM 2
#define FRAME_OBJ_NUM 2

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_Ungroup_3;
ui_interface_round_t *ui_g_Ungroup_fric_op = (ui_interface_round_t *)&(ui_g_Ungroup_3.data[0]);
ui_interface_round_t *ui_g_Ungroup_spin_op = (ui_interface_round_t *)&(ui_g_Ungroup_3.data[1]);

void _ui_init_g_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_3.data[i].figure_name[0] = FRAME_ID;
        ui_g_Ungroup_3.data[i].figure_name[1] = GROUP_ID;
        ui_g_Ungroup_3.data[i].figure_name[2] = i + START_ID;
        ui_g_Ungroup_3.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_Ungroup_3.data[i].operate_tpyel = 0;
    }

    ui_g_Ungroup_fric_op->figure_tpye = 2;
    ui_g_Ungroup_fric_op->layer = 2;
    ui_g_Ungroup_fric_op->r = 23;
    ui_g_Ungroup_fric_op->start_x = 271;
    ui_g_Ungroup_fric_op->start_y = 710;
    ui_g_Ungroup_fric_op->color = 2;
    ui_g_Ungroup_fric_op->width = 5;

    ui_g_Ungroup_spin_op->figure_tpye = 2;
    ui_g_Ungroup_spin_op->layer = 2;
    ui_g_Ungroup_spin_op->r = 23;
    ui_g_Ungroup_spin_op->start_x = 271;
    ui_g_Ungroup_spin_op->start_y = 649;
    ui_g_Ungroup_spin_op->color = 2;
    ui_g_Ungroup_spin_op->width = 5;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}

void _ui_update_g_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_3.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}

void _ui_remove_g_Ungroup_3() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_3.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_3);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_3, sizeof(ui_g_Ungroup_3));
}
