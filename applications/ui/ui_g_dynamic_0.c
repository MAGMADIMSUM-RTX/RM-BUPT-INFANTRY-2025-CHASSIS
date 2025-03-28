//
// Created by RM UI Designer
//

#include "ui_g_dynamic_0.h"
#include "cmsis_os.h"

#define FRAME_ID 0
#define GROUP_ID 1
#define START_ID 0
#define OBJ_NUM 5
#define FRAME_OBJ_NUM 5

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_dynamic_0;
ui_interface_arc_t *ui_g_dynamic_spinner = (ui_interface_arc_t *)&(ui_g_dynamic_0.data[0]);
ui_interface_round_t *ui_g_dynamic_fric = (ui_interface_round_t *)&(ui_g_dynamic_0.data[1]);
ui_interface_line_t *ui_g_dynamic_Line_angle = (ui_interface_line_t *)&(ui_g_dynamic_0.data[2]);
ui_interface_rect_t *ui_g_dynamic_auto_aim = (ui_interface_rect_t *)&(ui_g_dynamic_0.data[3]);
ui_interface_line_t *ui_g_dynamic_aim_line0 = (ui_interface_line_t *)&(ui_g_dynamic_0.data[4]);

void _ui_init_g_dynamic_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_dynamic_0.data[i].figure_name[0] = FRAME_ID;
        ui_g_dynamic_0.data[i].figure_name[1] = GROUP_ID;
        ui_g_dynamic_0.data[i].figure_name[2] = i + START_ID;
        ui_g_dynamic_0.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_dynamic_0.data[i].operate_tpyel = 0;
    }

    ui_g_dynamic_spinner->figure_tpye = 4;
    ui_g_dynamic_spinner->layer = 0;
    ui_g_dynamic_spinner->rx = 50;
    ui_g_dynamic_spinner->ry = 50;
    ui_g_dynamic_spinner->start_x = 1582;
    ui_g_dynamic_spinner->start_y = 740;
    ui_g_dynamic_spinner->color = 3;
    ui_g_dynamic_spinner->width = 12;
    ui_g_dynamic_spinner->start_angle = 30;
    ui_g_dynamic_spinner->end_angle = 330;

    ui_g_dynamic_fric->figure_tpye = 2;
    ui_g_dynamic_fric->layer = 0;
    ui_g_dynamic_fric->r = 10;
    ui_g_dynamic_fric->start_x = 1585;
    ui_g_dynamic_fric->start_y = 740;
    ui_g_dynamic_fric->color = 0;
    ui_g_dynamic_fric->width = 20;

    ui_g_dynamic_Line_angle->figure_tpye = 0;
    ui_g_dynamic_Line_angle->layer = 1;
    ui_g_dynamic_Line_angle->start_x = 1310;
    ui_g_dynamic_Line_angle->start_y = 540;
    ui_g_dynamic_Line_angle->end_x = 1340;
    ui_g_dynamic_Line_angle->end_y = 540;
    ui_g_dynamic_Line_angle->color = 0;
    ui_g_dynamic_Line_angle->width = 5;

    ui_g_dynamic_auto_aim->figure_tpye = 1;
    ui_g_dynamic_auto_aim->layer = 0;
    ui_g_dynamic_auto_aim->start_x = 530;
    ui_g_dynamic_auto_aim->start_y = 258;
    ui_g_dynamic_auto_aim->color = 6;
    ui_g_dynamic_auto_aim->width = 6;
    ui_g_dynamic_auto_aim->end_x = 1361;
    ui_g_dynamic_auto_aim->end_y = 833;

    ui_g_dynamic_aim_line0->figure_tpye = 2;
    ui_g_dynamic_aim_line0->layer = 0;
    ui_g_dynamic_aim_line0->start_x = 1585;
    ui_g_dynamic_aim_line0->start_y = 540;
    ui_g_dynamic_aim_line0->end_x = 1620;
    ui_g_dynamic_aim_line0->end_y = 540;
    ui_g_dynamic_aim_line0->color = 8;
    ui_g_dynamic_aim_line0->width = 20;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_dynamic_0);
    SEND_MESSAGE((uint8_t *) &ui_g_dynamic_0, sizeof(ui_g_dynamic_0));
}

void _ui_update_g_dynamic_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_dynamic_0.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_dynamic_0);
    SEND_MESSAGE((uint8_t *) &ui_g_dynamic_0, sizeof(ui_g_dynamic_0));
}

void _ui_remove_g_dynamic_0() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_dynamic_0.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_dynamic_0);
    SEND_MESSAGE((uint8_t *) &ui_g_dynamic_0, sizeof(ui_g_dynamic_0));
}
