//
// Created by RM UI Designer
//

#include "ui_g_Ungroup_1.h"

#define FRAME_ID 0
#define GROUP_ID 0
#define START_ID 1
#define OBJ_NUM 6
#define FRAME_OBJ_NUM 7

CAT(ui_, CAT(FRAME_OBJ_NUM, _frame_t)) ui_g_Ungroup_1;
ui_interface_rect_t *ui_g_Ungroup_Rect1 = (ui_interface_rect_t *)&(ui_g_Ungroup_1.data[0]);
ui_interface_rect_t *ui_g_Ungroup_Rect2 = (ui_interface_rect_t *)&(ui_g_Ungroup_1.data[1]);
ui_interface_line_t *ui_g_Ungroup_NewLine = (ui_interface_line_t *)&(ui_g_Ungroup_1.data[2]);
ui_interface_round_t *ui_g_Ungroup_NewRound = (ui_interface_round_t *)&(ui_g_Ungroup_1.data[3]);
ui_interface_ellipse_t *ui_g_Ungroup_NewEllipse = (ui_interface_ellipse_t *)&(ui_g_Ungroup_1.data[4]);
ui_interface_arc_t *ui_g_Ungroup_NewArc = (ui_interface_arc_t *)&(ui_g_Ungroup_1.data[5]);

void _ui_init_g_Ungroup_1() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_1.data[i].figure_name[0] = FRAME_ID;
        ui_g_Ungroup_1.data[i].figure_name[1] = GROUP_ID;
        ui_g_Ungroup_1.data[i].figure_name[2] = i + START_ID;
        ui_g_Ungroup_1.data[i].operate_tpyel = 1;
    }
    for (int i = OBJ_NUM; i < FRAME_OBJ_NUM; i++) {
        ui_g_Ungroup_1.data[i].operate_tpyel = 0;
    }

    ui_g_Ungroup_Rect1->figure_tpye = 1;
    ui_g_Ungroup_Rect1->layer = 0;
    ui_g_Ungroup_Rect1->start_x = 155;
    ui_g_Ungroup_Rect1->start_y = 618;
    ui_g_Ungroup_Rect1->color = 0;
    ui_g_Ungroup_Rect1->width = 1;
    ui_g_Ungroup_Rect1->end_x = 215;
    ui_g_Ungroup_Rect1->end_y = 668;

    ui_g_Ungroup_Rect2->figure_tpye = 1;
    ui_g_Ungroup_Rect2->layer = 0;
    ui_g_Ungroup_Rect2->start_x = 136;
    ui_g_Ungroup_Rect2->start_y = 426;
    ui_g_Ungroup_Rect2->color = 1;
    ui_g_Ungroup_Rect2->width = 1;
    ui_g_Ungroup_Rect2->end_x = 278;
    ui_g_Ungroup_Rect2->end_y = 568;

    ui_g_Ungroup_NewLine->figure_tpye = 0;
    ui_g_Ungroup_NewLine->layer = 0;
    ui_g_Ungroup_NewLine->start_x = 386;
    ui_g_Ungroup_NewLine->start_y = 583;
    ui_g_Ungroup_NewLine->end_x = 436;
    ui_g_Ungroup_NewLine->end_y = 633;
    ui_g_Ungroup_NewLine->color = 0;
    ui_g_Ungroup_NewLine->width = 1;

    ui_g_Ungroup_NewRound->figure_tpye = 2;
    ui_g_Ungroup_NewRound->layer = 0;
    ui_g_Ungroup_NewRound->r = 89;
    ui_g_Ungroup_NewRound->start_x = 584;
    ui_g_Ungroup_NewRound->start_y = 543;
    ui_g_Ungroup_NewRound->color = 4;
    ui_g_Ungroup_NewRound->width = 1;

    ui_g_Ungroup_NewEllipse->figure_tpye = 3;
    ui_g_Ungroup_NewEllipse->layer = 0;
    ui_g_Ungroup_NewEllipse->rx = 90;
    ui_g_Ungroup_NewEllipse->ry = 50;
    ui_g_Ungroup_NewEllipse->start_x = 833;
    ui_g_Ungroup_NewEllipse->start_y = 582;
    ui_g_Ungroup_NewEllipse->color = 0;
    ui_g_Ungroup_NewEllipse->width = 1;

    ui_g_Ungroup_NewArc->figure_tpye = 4;
    ui_g_Ungroup_NewArc->layer = 0;
    ui_g_Ungroup_NewArc->rx = 50;
    ui_g_Ungroup_NewArc->ry = 50;
    ui_g_Ungroup_NewArc->start_x = 1021;
    ui_g_Ungroup_NewArc->start_y = 488;
    ui_g_Ungroup_NewArc->color = 0;
    ui_g_Ungroup_NewArc->width = 4;
    ui_g_Ungroup_NewArc->start_angle = 30;
    ui_g_Ungroup_NewArc->end_angle = 300;


    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}

void _ui_update_g_Ungroup_1() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_1.data[i].operate_tpyel = 2;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}

void _ui_remove_g_Ungroup_1() {
    for (int i = 0; i < OBJ_NUM; i++) {
        ui_g_Ungroup_1.data[i].operate_tpyel = 3;
    }

    CAT(ui_proc_, CAT(FRAME_OBJ_NUM, _frame))(&ui_g_Ungroup_1);
    SEND_MESSAGE((uint8_t *) &ui_g_Ungroup_1, sizeof(ui_g_Ungroup_1));
}
