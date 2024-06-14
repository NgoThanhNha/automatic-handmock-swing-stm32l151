/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/06/2024
 ******************************************************************************
**/

#include "screen_setting.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"
#include "console.h"
#include "button.h"
#include "buzzer.h"
#include "screen_manager.h"
#include "view_render.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"

#include "screen_main.h"
#include "screen_network.h"
#include "screen_power.h"
#include "screen_track.h"

#include <math.h>

static void view_screen_setting_init();
static void view_screen_setting_update();

screen_setting_info_t screen_setting_info;

void screen_setting_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_SETTING_ENTRY\n");
        view_screen_setting_init();
        view_screen_setting_update();
        break;

    case SIG_BUTTON_UP_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_DOWN_PRESSED\n");
        if (screen_setting_info.cursor_select == 0) {
            screen_setting_info.cursor_select = 3;
        }
        else {
            screen_setting_info.cursor_select--;
        }
        /* view screen update */
        view_screen_setting_update();
        break;

    case SIG_BUTTON_DOWN_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_UP_PRESSED\n");
        screen_setting_info.cursor_select++;
        if (screen_setting_info.cursor_select == 4) {
            screen_setting_info.cursor_select = 0;
        }
        /* view screen update */
        view_screen_setting_update();
        break;

    case SIG_BUTTON_MODE_PRESSED:
        switch (screen_setting_info.cursor_select) {
        case 0:
            screen_setting_info.cursor_select = 0;
            view_render_force_clear();
            SCREEN_TRANS(&screen_network_handler);
            break;

        case 1:
            screen_setting_info.cursor_select = 0;
            view_render_force_clear();
            SCREEN_TRANS(&screen_power_handler);
            break;

        case 2:
            screen_setting_info.cursor_select = 0;
            view_render_force_clear();
            SCREEN_TRANS(&screen_track_handler);
            break;

        case 3:
            screen_setting_info.cursor_select = 0;
            view_render_force_clear();
            SCREEN_TRANS(&screen_main_handler);
            break;
        
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void view_screen_setting_init() {
    view_render_fill_rect(&view_render_static, 10, 5, 300, 30, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 12, "SETTING", 2, BLACK_COLOR);

    /* draw frame */
    view_render_draw_line(&view_render_static, 10, 40, 310, 40, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 41, 310, 41, WHITE_COLOR);
    view_render_draw_line(&view_render_dynamic, 310, 47, 310, 170, WHITE_COLOR);

    /* draw text */
    view_render_print_string(&view_render_static, 20, 55, "NETWORK", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 85, "POWER MONITOR", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 115, "TRACK", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 145, "BACK", 2, WHITE_COLOR);
}

void view_screen_setting_update() {
    view_render_clear(&view_render_dynamic);
    view_render_draw_line(&view_render_dynamic, 310, 47, 310, 170, WHITE_COLOR);

    /* view cursor */
    switch (screen_setting_info.cursor_select){
    case 0:
        view_render_draw_rect(&view_render_dynamic, 10, 47, 250, 30, CYAN_COLOR);
        view_render_fill_rect(&view_render_dynamic, 307, 47, 6, 20, WHITE_COLOR);
        break;

    case 1:
        view_render_draw_rect(&view_render_dynamic, 10, 77, 250, 30, CYAN_COLOR);
        view_render_fill_rect(&view_render_dynamic, 307, 82, 6, 20, WHITE_COLOR);
        break;

    case 2:
        view_render_draw_rect(&view_render_dynamic, 10, 107, 250, 30, CYAN_COLOR);
        view_render_fill_rect(&view_render_dynamic, 307, 117, 6, 20, WHITE_COLOR);
        break;

    case 3:
        view_render_draw_rect(&view_render_dynamic, 10, 137, 250, 30, CYAN_COLOR);
        view_render_fill_rect(&view_render_dynamic, 307, 146, 6, 20, WHITE_COLOR);
        break;
    
    default:
        break;
    }
}