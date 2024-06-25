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

#include "bitmaps.h"
#include "screen_main.h"

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
    view_render_draw_bitmap(&view_render_static, 95, 20, 120, 98, (uint16_t*)big_handmock_icon);
    view_render_print_string(&view_render_static, 15, 130, "Automatic Handmock Swing", 2, GRAY_COLOR);
}