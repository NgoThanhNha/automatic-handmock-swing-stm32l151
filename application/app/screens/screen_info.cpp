/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/06/2024
 ******************************************************************************
**/

#include "screen_info.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"
#include "console.h"
#include "screen_manager.h"
#include "view_render.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"
#include "screen_main.h"

#include <math.h>

static void view_screen_info_init();

void screen_info_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_INFO_ENTRY\n");
        view_screen_info_init();
        timer_set(TASK_DISPLAY_ID, SIG_SCREEN_TRANS, 2000, TIMER_ONE_SHOT);
        break;

    case SIG_SCREEN_TRANS:
        view_render_force_clear();
        SCREEN_TRANS(&screen_main_handler);
        break;

    default:
        break;
    }
}

void view_screen_info_init() {
    view_render_print_string(&view_render_static, 60, 20, " ___  ____  _  _ ", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 60, 37, "/ __)(_  _)( )/ )", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 60, 54, "\\__ \\  )(  (   (", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 60, 71, "(___/ (__) (_)\\_)", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 15, 110, "Automatic Handmock Swing", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 15, 135, "App version:", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 170, 135, "1.0", 2, GREEN_COLOR);
}