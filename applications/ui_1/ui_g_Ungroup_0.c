//
// Created by RM UI Designer
//

#include "ui_g_Ungroup_0.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 0
#define OBJ_NUM 2
#define FRAME_OBJ_NUM 2

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_Ungroup_0;
ui_interface_line_t *ui_g_Ungroup_Line1 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[0]);
ui_interface_line_t *ui_g_Ungroup_Line2 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[1]);

void _ui_init_g_Ungroup_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_Ungroup_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_Ungroup_0.data[i].figure_name[2] = i + START_ID;
        ui_g_Ungroup_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_Ungroup_0.data[i].operate_tpyel = 0;
    }

    ui_g_Ungroup_Line1->figure_tpye = 0;
    ui_g_Ungroup_Line1->layer = 0;
    ui_g_Ungroup_Line1->start_x = 625;
    ui_g_Ungroup_Line1->start_y = 451;
    ui_g_Ungroup_Line1->end_x = 805;
    ui_g_Ungroup_Line1->end_y = 631;
    ui_g_Ungroup_Line1->color = 0;
    ui_g_Ungroup_Line1->width = 1;

    ui_g_Ungroup_Line2->figure_tpye = 0;
    ui_g_Ungroup_Line2->layer = 0;
    ui_g_Ungroup_Line2->start_x = 1062;
    ui_g_Ungroup_Line2->start_y = 538;
    ui_g_Ungroup_Line2->end_x = 1242;
    ui_g_Ungroup_Line2->end_y = 538;
    ui_g_Ungroup_Line2->color = 6;
    ui_g_Ungroup_Line2->width = 2;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}

void _ui_update_g_Ungroup_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}

void _ui_remove_g_Ungroup_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_0);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_0, sizeof(ui_g_Ungroup_0));
}
