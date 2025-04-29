//
// Created by RM UI Designer
//

#include "ui_g_Ungroup_0.h"
#include "cmsis_os.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 0
#define OBJ_NUM 5
#define FRAME_OBJ_NUM 5

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_Ungroup_0;
ui_interface_line_t *ui_g_Ungroup_Line0 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[0]);
ui_interface_line_t *ui_g_Ungroup_Line15 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[1]);
ui_interface_line_t *ui_g_Ungroup_Line_15 = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[2]);
ui_interface_line_t *ui_g_Ungroup_forword_line_left = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[3]);
ui_interface_line_t *ui_g_Ungroup_forword_line_right = (ui_interface_line_t *)&(ui_g_Ungroup_0.data[4]);

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
    ui_g_Ungroup_Line0->start_x = 1310;
    ui_g_Ungroup_Line0->start_y = 540;
    ui_g_Ungroup_Line0->end_x = 1340;
    ui_g_Ungroup_Line0->end_y = 540;
    ui_g_Ungroup_Line0->color = 8;
    ui_g_Ungroup_Line0->width = 5;

    ui_g_Ungroup_Line15->figure_tpye = 0;
    ui_g_Ungroup_Line15->layer = 0;
    ui_g_Ungroup_Line15->start_x = 1247;
    ui_g_Ungroup_Line15->start_y = 741;
    ui_g_Ungroup_Line15->end_x = 1270;
    ui_g_Ungroup_Line15->end_y = 758;
    ui_g_Ungroup_Line15->color = 8;
    ui_g_Ungroup_Line15->width = 5;

    ui_g_Ungroup_Line_15->figure_tpye = 0;
    ui_g_Ungroup_Line_15->layer = 0;
    ui_g_Ungroup_Line_15->start_x = 1247;
    ui_g_Ungroup_Line_15->start_y = 339;
    ui_g_Ungroup_Line_15->end_x = 1270;
    ui_g_Ungroup_Line_15->end_y = 322;
    ui_g_Ungroup_Line_15->color = 8;
    ui_g_Ungroup_Line_15->width = 5;

    ui_g_Ungroup_forword_line_left->figure_tpye = 0;
    ui_g_Ungroup_forword_line_left->layer = 0;
    ui_g_Ungroup_forword_line_left->start_x = 580;
    ui_g_Ungroup_forword_line_left->start_y = 46;
    ui_g_Ungroup_forword_line_left->end_x = 878;
    ui_g_Ungroup_forword_line_left->end_y = 344;
    ui_g_Ungroup_forword_line_left->color = 1;
    ui_g_Ungroup_forword_line_left->width = 5;

    ui_g_Ungroup_forword_line_right->figure_tpye = 0;
    ui_g_Ungroup_forword_line_right->layer = 0;
    ui_g_Ungroup_forword_line_right->start_x = 1340;
    ui_g_Ungroup_forword_line_right->start_y = 46;
    ui_g_Ungroup_forword_line_right->end_x = 1042;
    ui_g_Ungroup_forword_line_right->end_y = 344;
    ui_g_Ungroup_forword_line_right->color = 1;
    ui_g_Ungroup_forword_line_right->width = 5;


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
