/*
 * @Author: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @Date: 2025-03-25 23:04:07
 * @LastEditors: MAGMADIMSUM madmaliu@bupt.edu.cn
 * @LastEditTime: 2025-03-25 23:13:29
 * @FilePath: \ui\ui_g_sign_text_0.c
 * @Description: 
 * 
 */
//
// Created by RM UI Designer
//

#include "ui_g_sign_text_0.h"
#include "string.h"

#define FRAME_ID 0
#define GROUP_ID 6
#define START_ID 0

ui_string_frame_t ui_g_sign_text_0;

ui_interface_string_t *ui_g_sign_text_NewText = &ui_g_sign_text_0.option;

void _ui_init_g_sign_text_0()
{
    ui_g_sign_text_0.option.figure_name[0] = FRAME_ID;
    ui_g_sign_text_0.option.figure_name[1] = GROUP_ID;
    ui_g_sign_text_0.option.figure_name[2] = START_ID;
    ui_g_sign_text_0.option.operate_tpyel = 1;
    ui_g_sign_text_0.option.figure_tpye = 7;
    ui_g_sign_text_0.option.layer = 3;
    ui_g_sign_text_0.option.font_size = 20;
    ui_g_sign_text_0.option.start_x = 1534;
    ui_g_sign_text_0.option.start_y = 792;
    ui_g_sign_text_0.option.color = 2;
    ui_g_sign_text_0.option.str_length = 3;
    ui_g_sign_text_0.option.width = 2;
    strcpy(ui_g_sign_text_NewText->string, "пе╨есе");

    ui_proc_string_frame(&ui_g_sign_text_0);
    SEND_MESSAGE((uint8_t *)&ui_g_sign_text_0, sizeof(ui_g_sign_text_0));
}

void _ui_update_g_sign_text_0()
{
    ui_g_sign_text_0.option.operate_tpyel = 2;

    ui_proc_string_frame(&ui_g_sign_text_0);
    SEND_MESSAGE((uint8_t *)&ui_g_sign_text_0, sizeof(ui_g_sign_text_0));
}

void _ui_remove_g_sign_text_0()
{
    ui_g_sign_text_0.option.operate_tpyel = 3;

    ui_proc_string_frame(&ui_g_sign_text_0);
    SEND_MESSAGE((uint8_t *)&ui_g_sign_text_0, sizeof(ui_g_sign_text_0));
}