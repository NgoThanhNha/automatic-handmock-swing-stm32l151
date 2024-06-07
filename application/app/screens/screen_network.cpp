/**
 ******************************************************************************
 * @author: Nark
 * @date:   07/06/2024
 ******************************************************************************
**/

#include "screen_network.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "platform.h"
#include "console.h"
#include "screen_manager.h"
#include "view_render.h"
#include "utils.h"

#include "app.h"
#include "task_list.h"
#include "task_display.h"
#include "link_phy.h"

#include "screen_main.h"
#include "screen_setting.h"

screen_network_info_t screen_network_info;
static void screen_network_init();
static void screen_network_update();

char ssid_display[30];
char password_display[30];

void screen_network_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SCREEN_ENTRY:
        APP_PRINT("[SCREEN] SCREEN_NETWORK_ENTRY\n");
        screen_network_init();
        screen_network_update();
        task_post_pure_msg(TASK_SM_ID, SIG_SM_REQ_WIFI_INFO);
        break;
    
    case SIG_SCREEN_UPDATE:
        APP_PRINT("[SCREEN] SIG_SCREEN_UPDATE\n");
        screen_network_update();
        break;

    case SIG_BUTTON_UP_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_UP_PRESSED\n");
        task_post_pure_msg(TASK_SM_ID, SIG_SM_REQ_WIFI_RECONNECT);
        main_screen_info.wifi_status = WL_STATE_RECONNECTING;
        screen_network_update();
        break;

    case SIG_BUTTON_DOWN_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_DOWN_PRESSED\n");
        task_post_pure_msg(TASK_SM_ID, SIG_SM_REQ_WIFI_RECHANGE);
        main_screen_info.wifi_status = WL_STATE_RECHANGING;
        screen_network_update();
        break;

    case SIG_BUTTON_MODE_PRESSED:
        APP_PRINT("[SCREEN] SIG_BUTTON_MODE_PRESSED\n");
        view_render_force_clear();
        SCREEN_TRANS(&screen_setting_handler);
        break;

    default:
        break;
    }
}

void screen_network_init() {
    /* draw frame */
    view_render_fill_rect(&view_render_static, 10, 5, 300, 30, WHITE_COLOR);
    view_render_print_string(&view_render_static, 20, 12, "NETWORK", 2, BLACK_COLOR);
    view_render_draw_line(&view_render_static, 10, 40, 310, 40, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 41, 310, 41, WHITE_COLOR);

    /* wifi info */
    view_render_print_string(&view_render_static, 30, 55, "Wifi status: ", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 30, 85, "SSID: ", 2, WHITE_COLOR);
    view_render_print_string(&view_render_static, 30, 115, "Password: ", 2, WHITE_COLOR);

    /* need update */
    view_render_print_string(&view_render_static, 13, 150, "Reconnect", 2, CYAN_COLOR);
    view_render_print_string(&view_render_static, 158, 150, "Change", 2, YELLOW_COLOR);
    view_render_print_string(&view_render_static, 268, 150, "Back", 2, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 143, 310, 143, WHITE_COLOR);
    view_render_draw_line(&view_render_static, 10, 144, 310, 144, WHITE_COLOR);
}

void screen_network_update() {
    view_render_clear(&view_render_dynamic);

    /* display wl info */
    mem_cpy((char*)(&ssid_display[0]), (const char*)(&link_phy_wl_info.ssid[0]), 30);
    mem_cpy((char*)(&password_display[0]), (const char*)(&link_phy_wl_info.password[0]), 30);
    view_render_print_string(&view_render_dynamic, 100, 85, (const char*)(&ssid_display[0]), 2, CYAN_COLOR);
    view_render_print_string(&view_render_dynamic, 150, 115, (const char*)(&password_display[0]), 2, CYAN_COLOR);
    
    switch (main_screen_info.wifi_status) {
    case WL_STATE_DISCONNECTED:
        view_render_print_string(&view_render_dynamic, 175, 55, "Disconnected", 2, ORANGE_COLOR);
        break; 

    case WL_STATE_CONNECTED:
        view_render_print_string(&view_render_dynamic, 180, 55, "Connected", 2, GREEN_COLOR);
        break;
    
    case WL_STATE_RECONNECTING:
        view_render_print_string(&view_render_dynamic, 175, 55, "Reconnecting", 2, ORANGE_COLOR);
        break;

    case WL_STATE_RECHANGING:
        view_render_print_string(&view_render_dynamic, 175, 55, "Rechanging", 2, YELLOW_COLOR);
        break; 

    default:
        break;
    }
}