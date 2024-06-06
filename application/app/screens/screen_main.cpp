/**
 ******************************************************************************
 * @author: Nark
 * @date:   19/05/2024
 ******************************************************************************
**/

#include "screen_main.h"

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
#include "dfplayer.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"
#include "task_pid.h"

#include "screen_setting.h"

static void view_screen_main_update();
static void view_screen_main_init();
static void view_icon_select(int16_t x0, int16_t y0);
screen_main_info_t main_screen_info;

void screen_main_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_MAIN_ENTRY\n");
        main_screen_info.music_volume = 20;
        view_screen_main_init();
        view_screen_main_update();
        break;

    case SIG_BUTTON_UP_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_UP_PRESSED\n");
        main_screen_info.cursor_select++;
        if (main_screen_info.cursor_select == 3) {
            main_screen_info.cursor_select = 0;
        }
        /* view screen update */
        view_screen_main_update();
        break;

    case SIG_BUTTON_DOWN_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_DOWN_PRESSED\n");
        switch (main_screen_info.cursor_select) {
        case 0:
            if (main_screen_info.music_volume != 0) {
                main_screen_info.music_volume -= 5;
            }
            dfplayer_set_volume(main_screen_info.music_volume);
            break;

        case 1:
            if (main_screen_info.speed == 0) {
                main_screen_info.speed = 2;
            }
            else {
                main_screen_info.speed--;
            }
            break;
        
        default:
            break;
        }

        /* view screen update */
        view_screen_main_update();
        break;

    case SIG_BUTTON_MODE_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_MODE_PRESSED\n");
        switch (main_screen_info.cursor_select) {
        case 0:
            main_screen_info.music_volume += 5;
            if (main_screen_info.music_volume == 31) {
                main_screen_info.music_volume = 31;
            }
            dfplayer_set_volume(main_screen_info.music_volume);
            break;

        case 1:
            main_screen_info.speed++;
            if (main_screen_info.speed == 3) {
                main_screen_info.speed = 0;
            }
            break;

        case 2:
            task_post_pure_msg(TASK_DISPLAY_ID, SIG_SCREEN_TRANS);
            break;
        
        default:
            break;
        }
        
        /* update screen */
        view_screen_main_update();
        break;

    case SIG_BUTTON_MODE_LONG_PRESSED:
        if (main_screen_info.music_state == MAIN_INFO_MUSIC_OFF) {
        main_screen_info.music_state = MAIN_INFO_MUSIC_ON;
        }
        else if (main_screen_info.music_state == MAIN_INFO_MUSIC_ON) {
        main_screen_info.music_state = MAIN_INFO_MUSIC_OFF;
        }
        /* update screen */
        view_screen_main_update();
        break;

    case SIG_SCREEN_TRANS:
        main_screen_info.cursor_select = 0;
        view_render_force_clear();
        SCREEN_TRANS(&screen_setting_handler);
        break;

    default:
        break;
    }
}

void view_screen_main_init() {
    /* frame */
    view_render_draw_line(&view_render_static, 10, 32, 310, 32, WHITE_COLOR);

    /* icons */
    view_render_draw_bitmap(&view_render_static, 15, 50, 100, 100, (uint16_t*)handmock_icon);
    view_render_draw_bitmap(&view_render_static, 10, 4, 30, 24, (uint16_t*)wifi_icon);
    view_render_draw_bitmap(&view_render_static, 275, 0, 30, 30, (uint16_t*)setting_icon);
    view_render_draw_bitmap(&view_render_static, 160, 45, 28, 29, (uint16_t*)music_icon);
    view_render_draw_bitmap(&view_render_static, 160, 90, 25, 25, (uint16_t*)speed_icon);
    view_render_draw_bitmap(&view_render_static, 160, 130, 25, 25, (uint16_t*)weight_icon);

    /* texts */
    view_render_print_string(&view_render_dynamic, 200, 52, "Stop", 2, ORANGE_COLOR);
    view_render_print_string(&view_render_dynamic, 200, 95, "Level 1", 2, GREEN_COLOR);
    view_render_print_string(&view_render_static, 200, 140, "...kg", 2, BROWN_COLOR);

    /* cursor */
    view_icon_select(140, 47);
}

void view_screen_main_update() {
    view_render_clear(&view_render_dynamic);

    /* view cursor select */
    switch (main_screen_info.cursor_select) {
    case 0:
        view_icon_select(140, 47);
        break;

    case 1:
        view_icon_select(140, 90);
        break;
    
    case 2:
        view_icon_select(260, 3);
        break;

    default:
        break;
    }

    /* view music_state */
    switch (main_screen_info.music_state) {
    case MAIN_INFO_MUSIC_ON:
        view_render_print_string(&view_render_dynamic, 200, 52, "Play", 2, GREEN_COLOR);
        dfplayer_play_continous();
        break;

    case MAIN_INFO_MUSIC_OFF:
        view_render_print_string(&view_render_dynamic, 200, 52, "Stop", 2, ORANGE_COLOR);
        dfplayer_stop();
        break;
    
    default:
        break;
    }

    /* view speed level */
    switch (main_screen_info.speed) {
    case MAIN_INFO_MOTOR_SPEED_LEVEL_1:
        view_render_print_string(&view_render_dynamic, 200, 95, "Level 1", 2, GREEN_COLOR);
        pid_set(VELOCITY_SET_LEVEL_1);
        break;

    case MAIN_INFO_MOTOR_SPEED_LEVEL_2:
        view_render_print_string(&view_render_dynamic, 200, 95, "Level 2", 2, YELLOW_COLOR);
        pid_set(VELOCITY_SET_LEVEL_2);
        break;
    
    case MAIN_INFO_MOTOR_SPEED_LEVEL_3:
        view_render_print_string(&view_render_dynamic, 200, 95, "Level 3", 2, ORANGE_COLOR);
        pid_set(VELOCITY_SET_LEVEL_3);
        break;

    default:
        break;
    }
}

void view_icon_select(int16_t x0, int16_t y0) {
    view_render_fill_triangle(&view_render_dynamic, x0, y0, x0 + 10, y0 + 10, x0, y0 + 20, GREEN_COLOR);
}