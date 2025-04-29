//
// Created by RM UI Designer
//

#ifndef UI_H
#define UI_H
#ifdef __cplusplus
extern "C"
{
#endif

#include "ui_interface.h"

#include "ui_g_line_0.h"

#define ui_init_g_line() \
    _ui_init_g_line_0()

#define ui_update_g_line() \
    _ui_update_g_line_0()

#define ui_remove_g_line() \
    _ui_remove_g_line_0()

#include "ui_g_Ungroup_0.h"
#include "ui_g_Ungroup_1.h"
#include "ui_g_Ungroup_2.h"
#include "ui_g_Ungroup_3.h"

#define ui_init_g_Ungroup() \
    _ui_init_g_Ungroup_0(); \
    _ui_init_g_Ungroup_1(); \
    _ui_init_g_Ungroup_2(); \
    _ui_init_g_Ungroup_3()

#define ui_update_g_Ungroup() \
    _ui_update_g_Ungroup_0(); \
    _ui_update_g_Ungroup_1(); \
    _ui_update_g_Ungroup_2(); \
    _ui_update_g_Ungroup_3()

#define ui_remove_g_Ungroup() \
    _ui_remove_g_Ungroup_0(); \
    _ui_remove_g_Ungroup_1(); \
    _ui_remove_g_Ungroup_2(); \
    _ui_remove_g_Ungroup_3()

#include "ui_g_l1_0.h"

#define ui_init_g_l1() \
    _ui_init_g_l1_0()

#define ui_update_g_l1() \
    _ui_update_g_l1_0()

#define ui_remove_g_l1() \
    _ui_remove_g_l1_0()

#include "ui_g_spin_cl_0.h"

#define ui_init_g_spin_cl() \
    _ui_init_g_spin_cl_0()

#define ui_update_g_spin_cl() \
    _ui_update_g_spin_cl_0()

#define ui_remove_g_spin_cl() \
    _ui_remove_g_spin_cl_0()

#include "ui_g_sign_0.h"

#define ui_init_g_sign() \
    _ui_init_g_sign_0()

#define ui_update_g_sign() \
    _ui_update_g_sign_0()

#define ui_remove_g_sign() \
    _ui_remove_g_sign_0()

#include "ui_g_sign_high_0.h"

#define ui_init_g_sign_high() \
    _ui_init_g_sign_high_0()

#define ui_update_g_sign_high() \
    _ui_update_g_sign_high_0()

#define ui_remove_g_sign_high() \
    _ui_remove_g_sign_high_0()

#include "ui_g_sign_text_0.h"

#define ui_init_g_sign_text() \
    _ui_init_g_sign_text_0()

#define ui_update_g_sign_text() \
    _ui_update_g_sign_text_0()

#define ui_remove_g_sign_text() \
    _ui_remove_g_sign_text_0()

#define ui_init()              \
    {                          \
        ui_init_g_line();      \
        ui_init_g_Ungroup();   \
        ui_init_g_l1();        \
        ui_init_g_spin_cl();   \
        ui_init_g_sign();      \
        ui_init_g_sign_high(); \
        ui_init_g_sign_text(); \
    }

#define ui_update()              \
    {                            \
        ui_update_g_line();      \
        ui_update_g_Ungroup();   \
        ui_update_g_l1();        \
        ui_update_g_spin_cl();   \
        ui_update_g_sign();      \
        ui_update_g_sign_high(); \
        ui_update_g_sign_text(); \
    }

#define ui_remove()              \
    {                            \
        ui_remove_g_line();      \
        ui_remove_g_Ungroup();   \
        ui_remove_g_l1();        \
        ui_remove_g_spin_cl();   \
        ui_remove_g_sign();      \
        ui_remove_g_sign_high(); \
        ui_remove_g_sign_text(); \
    }

#ifdef __cplusplus
}
#endif

#endif // UI_H
