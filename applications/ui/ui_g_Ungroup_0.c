//
// Created by RM UI Designer
//

#include "ui_g_Ungroup_0.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 0
#define OBJ_NUM 7
#define FRAME_OBJ_NUM 7

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_Ungroup_0;
ui_interface_line_t *ui_g_Ungroup_Line0 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[0]);
ui_interface_arc_t *ui_g_Ungroup_spinner = (ui_interface_arc_t *)&(ui_g_Ungroup_0.data[1]);
ui_interface_line_t *ui_g_Ungroup_Line15 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[2]);
ui_interface_line_t *ui_g_Ungroup_Line_15 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[3]);
ui_interface_line_t *ui_g_Ungroup_Lineangle = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[4]);
ui_interface_round_t *ui_g_Ungroup_fric = (ui_interface_round_t *)&(ui_g_Ungroup_0.data[5]);
ui_interface_round_t *ui_g_Ungroup_focus = (ui_interface_round_t *)&(ui_g_Ungroup_0.data[6]);

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

    ui_g_Ungroup_Line0->figure_tpye = 0;
    ui_g_Ungroup_Line0->layer = 0;
    ui_g_Ungroup_Line0->start_x = 1410;
    ui_g_Ungroup_Line0->start_y = 540;
    ui_g_Ungroup_Line0->end_x = 1440;
    ui_g_Ungroup_Line0->end_y = 540;
    ui_g_Ungroup_Line0->color = 8;
    ui_g_Ungroup_Line0->width = 10;

    ui_g_Ungroup_spinner->figure_tpye = 4;
    ui_g_Ungroup_spinner->layer = 0;
    ui_g_Ungroup_spinner->rx = 47;
    ui_g_Ungroup_spinner->ry = 47;
    ui_g_Ungroup_spinner->start_x = 1540;
    ui_g_Ungroup_spinner->start_y = 740;
    ui_g_Ungroup_spinner->color = 3;
    ui_g_Ungroup_spinner->width = 20;
    ui_g_Ungroup_spinner->start_angle = 215;
    ui_g_Ungroup_spinner->end_angle = 145;

    ui_g_Ungroup_Line15->figure_tpye = 0;
    ui_g_Ungroup_Line15->layer = 0;
    ui_g_Ungroup_Line15->start_x = 1328;
    ui_g_Ungroup_Line15->start_y = 798;
    ui_g_Ungroup_Line15->end_x = 1353;
    ui_g_Ungroup_Line15->end_y = 815;
    ui_g_Ungroup_Line15->color = 8;
    ui_g_Ungroup_Line15->width = 12;

    ui_g_Ungroup_Line_15->figure_tpye = 0;
    ui_g_Ungroup_Line_15->layer = 0;
    ui_g_Ungroup_Line_15->start_x = 1328;
    ui_g_Ungroup_Line_15->start_y = 281;
    ui_g_Ungroup_Line_15->end_x = 1353;
    ui_g_Ungroup_Line_15->end_y = 264;
    ui_g_Ungroup_Line_15->color = 8;
    ui_g_Ungroup_Line_15->width = 12;

    ui_g_Ungroup_Lineangle->figure_tpye = 0;
    ui_g_Ungroup_Lineangle->layer = 0;
    ui_g_Ungroup_Lineangle->start_x = 1304;
    ui_g_Ungroup_Lineangle->start_y = 534;
    ui_g_Ungroup_Lineangle->end_x = 1342;
    ui_g_Ungroup_Lineangle->end_y = 534;
    ui_g_Ungroup_Lineangle->color = 0;
    ui_g_Ungroup_Lineangle->width = 12;

    ui_g_Ungroup_fric->figure_tpye = 2;
    ui_g_Ungroup_fric->layer = 0;
    ui_g_Ungroup_fric->r = 8;
    ui_g_Ungroup_fric->start_x = 1543;
    ui_g_Ungroup_fric->start_y = 741;
    ui_g_Ungroup_fric->color = 8;
    ui_g_Ungroup_fric->width = 16;

    ui_g_Ungroup_focus->figure_tpye = 2;
    ui_g_Ungroup_focus->layer = 0;
    ui_g_Ungroup_focus->r = 500;
    ui_g_Ungroup_focus->start_x = 960;
    ui_g_Ungroup_focus->start_y = 540;
    ui_g_Ungroup_focus->color = 1;
    ui_g_Ungroup_focus->width = 2;

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
