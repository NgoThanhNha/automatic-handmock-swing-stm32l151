/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/06/2024
 ******************************************************************************
**/

#include "task_sm.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"
#include "console.h"
#include "platform.h"

#include "app.h"
#include "link_phy.h"
#include "task_list.h"
#include "task_pid.h"
#include "task_display.h"
#include "task_safety.h"

#include "screen_main.h"
#include "screen_network.h"

void task_sm_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_SM_REQ_WIFI_STATUS:
        APP_PRINT("[TASK_SM] SIG_SM_REQ_CHECK_WIFI_CONNECT\n");
        LINK_PHY_FORWARD_MSG_OUT(TASK_SM_ID, SIG_SM_REQ_WIFI_STATUS);
        break;

    case SIG_SM_REQ_WIFI_INFO:
        APP_PRINT("[TASK_SM] SIG_SM_REQ_WIFI_INFO\n");
        LINK_PHY_FORWARD_MSG_OUT(TASK_SM_ID, SIG_SM_REQ_WIFI_INFO);
        break;

    case SIG_SM_REQ_WIFI_RECONNECT:
        APP_PRINT("[TASK_SM] SIG_SM_REQ_WIFI_RECONNECT\n");
        LINK_PHY_FORWARD_MSG_OUT(TASK_SM_ID, SIG_SM_REQ_WIFI_RECONNECT);
        break;

    case SIG_SM_REQ_WIFI_RECHANGE:
        APP_PRINT("[TASK_SM] SIG_SM_REQ_WIFI_RECHANGE\n");
        LINK_PHY_FORWARD_MSG_OUT(TASK_SM_ID, SIG_SM_REQ_WIFI_RECHANGE);
        break;

    case SIG_SM_RES_WIFI_CONNECTED:
        APP_PRINT("[TASK_SM] SIG_SM_RES_WIFI_CONNECTED\n");
        main_screen_info.wifi_status = WL_STATE_CONNECTED;
        task_post_pure_msg(LINK_PHY_ID, SIG_LINK_PHY_SEND_DATA);
        break;

    case SIG_SM_RES_WIFI_DISCONNECTED:
        APP_PRINT("[TASK_SM] SIG_SM_RES_WIFI_DISCONNECTED\n");
        main_screen_info.wifi_status = WL_STATE_DISCONNECTED;
        LINK_PHY_FORWARD_MSG_OUT(TASK_SM_ID, SIG_SM_REQ_WIFI_RECONNECT);
        break;

    default:
        break;
    }
}