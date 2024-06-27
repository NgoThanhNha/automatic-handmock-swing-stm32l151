/**
 ******************************************************************************
 * @author: Nark
 * @date:   08/06/2024
 ******************************************************************************
**/

#include "screen_power.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"
#include "console.h"
#include "button.h"
#include "screen_manager.h"
#include "view_render.h"

#include "bitmaps.h"
#include "st7789.h"
#include "ina219.h"
#include "dfplayer.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"
#include "task_pid.h"
#include "task_safety.h"
#include "link_phy.h"

#include "screen_setting.h"

static void view_screen_power_init();
static void view_screen_power_update();

void screen_power_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_POWER_ENTRY\n");
        timer_set(TASK_DISPLAY_ID, SIG_SCREEN_UPDATE, 1000, TIMER_PERIODIC);
        view_screen_power_init();
        break;

    case SIG_SCREEN_UPDATE:
        view_screen_power_update();
        break;
    
    case SIG_BUTTON_MODE_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_MODE_PRESSED\n");
        timer_remove(TASK_DISPLAY_ID, SIG_SCREEN_UPDATE);
        view_render_force_clear();
        SCREEN_TRANS(&screen_setting_handler);
        break;

    default:
        break;
    }
}

void view_screen_power_init() {
    /* draw frame */
    view_render_fill_rect(&view_render_static, 10, 5, 300, 30, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 12, "POWER MONITOR", 2, BLACK_COLOR);
    view_render_draw_line(&view_render_static, 10, 40, 310, 40, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 41, 310, 41, WHITE_COLOR);

    /* draw motor voltage - current */
    view_render_print_string(&view_render_static, 25, 65, "Motor voltage: ", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 275, 65, "V", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 25, 100, "Motor current: ", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 275, 100, "mA", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 260, 150, "Back", 2, GRAY_COLOR);

    view_render_print_float(&view_render_dynamic, 195, 65, safety.motor_voltage, 2, GREEN_COLOR);
    view_render_print_float(&view_render_dynamic, 195, 100, safety.motor_current, 2, YELLOW_COLOR);
}

void view_screen_power_update() {
    view_render_clear(&view_render_dynamic);
    view_render_print_float(&view_render_dynamic, 195, 65, safety.motor_voltage, 2, GREEN_COLOR);
    view_render_print_float(&view_render_dynamic, 195, 100, safety.motor_current, 2, YELLOW_COLOR);
}