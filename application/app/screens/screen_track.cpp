/**
 ******************************************************************************
 * @author: Nark
 * @date:   14/06/2024
 ******************************************************************************
**/

#include "screen_track.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"
#include "console.h"
#include "button.h"
#include "screen_manager.h"
#include "hard_timer.h"
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

#include "screen_main.h"
#include "screen_setting.h"

static void view_screen_track_init();
static void view_screen_track_update();
static void view_icon_select(int16_t x0, int16_t y0);

uint8_t screen_track_cursor;
screen_track_info_t screen_track_info;

void screen_track_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_MAIN_ENTRY\n");
        view_screen_track_init();
        view_screen_track_update();
        break;

    case SIG_BUTTON_UP_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_UP_PRESSED\n");
        screen_track_cursor++;
        if (screen_track_cursor == 4) {
            screen_track_cursor = 0;
        }
        view_screen_track_update();
        break;

    case SIG_BUTTON_DOWN_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_DOWN_PRESSED\n");
        switch (screen_track_cursor) {
        case 0:
            screen_track_info.music_status = MUSIC_OFF;
            dfplayer_stop();
            break;
        
        case 1:
            if (screen_track_info.volume != 0) {
                screen_track_info.volume -= 5;
            }
            dfplayer_set_volume(screen_track_info.volume);
            break;

        case 2:
            dfplayer_play_prev();
            break; 

        default:
            break;
        }

        /* view screen update */
        view_screen_track_update();
        break;

    case SIG_BUTTON_MODE_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_DOWN_PRESSED\n");
        switch (screen_track_cursor) {
        case 0:
            screen_track_info.music_status = MUSIC_ON;
            dfplayer_enable_loop();
            delay_ms(5);
            dfplayer_set_volume(screen_track_info.volume);
            break;
        
        case 1:
            screen_track_info.volume += 5;
            if (screen_track_info.volume >= 30) {
                screen_track_info.volume = 30;
            }
            dfplayer_set_volume(screen_track_info.volume);
            break;

        case 2:
            dfplayer_play_next();
            break; 

        case 3:
            task_post_pure_msg(TASK_DISPLAY_ID, SIG_SCREEN_TRANS);
            break; 

        default:
            break;
        }

        /* view screen update */
        view_screen_track_update();
        break;

    case SIG_BUTTON_MODE_LONG_PRESSED:
        break;

    case SIG_SCREEN_TRANS:
        screen_track_cursor = 0;
        view_render_force_clear();
        SCREEN_TRANS(&screen_setting_handler);
        break;
    }
}

void view_screen_track_init() {
    /* draw frame */
    view_render_fill_rect(&view_render_static, 10, 5, 300, 30, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 12, "TRACK", 2, BLACK_COLOR);
    view_render_draw_line(&view_render_static, 10, 40, 310, 40, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 41, 310, 41, WHITE_COLOR);

    /* draw icon */
    view_render_draw_bitmap(&view_render_static, 30, 75, 80, 84, (uint16_t*)big_music_icon);

    /* draw volume */
    view_render_print_string(&view_render_static, 150, 60, "Status:", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 150, 90, "Volume:", 2, ORANGE_COLOR);
    view_render_print_string(&view_render_static, 150, 120, "Track: << >>", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 150, 150, "Back", 2, GRAY_COLOR);
}

void view_screen_track_update() {
    view_render_clear(&view_render_dynamic);
    switch (screen_track_cursor) {
    case 0:
        view_icon_select(130, 55);
        break;
    
    case 1:
        view_icon_select(130, 85);
        break;

    case 2:
        view_icon_select(130, 115);
        break;

    case 3:
        view_icon_select(130, 145);
        break;

    default:
        break;
    }

    switch (screen_track_info.music_status) {
    case MUSIC_ON:
        view_render_print_string(&view_render_dynamic, 250, 60, "Play", 2, YELLOW_COLOR);
        break;
    
    case MUSIC_OFF:
        view_render_print_string(&view_render_dynamic, 250, 60, "Stop", 2, YELLOW_COLOR);
        break;

    default:
        break;
    }

    /* update volume */
    view_render_print_integer(&view_render_dynamic, 250, 90, screen_track_info.volume, 2, GREEN_COLOR);
}

void view_icon_select(int16_t x0, int16_t y0) {
    view_render_fill_triangle(&view_render_dynamic, x0, y0, x0 + 10, y0 + 10, x0, y0 + 20, GREEN_COLOR);
}