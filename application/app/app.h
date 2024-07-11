/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __APP_H__
#define __APP_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>

extern void main_app();

/*---------------------------------------------------------------------------*/
/*                            APP DEFINE SIGNALS                             */
/*---------------------------------------------------------------------------*/
enum app_signals {
    /* TASK_PID */
    SIG_VELOCITY_CALCULATE = 0x00,
    SIG_PRINT_VELOCITY,
    SIG_PID_INIT,

    /* TASK DISPLAY */
    SIG_SCREEN_TRANS,
    SIG_SCREEN_ANIMATION,
    SIG_SCREEN_UPDATE,
    
    SIG_BUTTON_UP_PRESSED,
    SIG_BUTTON_DOWN_PRESSED,
    SIG_BUTTON_MODE_PRESSED,
    SIG_BUTTON_MODE_LONG_PRESSED,

    /* TASK SAFETY */
    SIG_CHECK_CURRENT_WARNING,
    SIG_CURRENT_CALCULATE,
    SIG_MASS_CALCULATE,
    SIG_CHECK_MAX_CURRENT,

    /* ESP8266 UART LINK */
    SIG_LINK_PHY_GET_BUFF,

    SIG_LINK_PHY_GET_MSG_RES,
    SIG_LINK_PHY_GET_WIFI_RES,
    SIG_LINK_PHY_SEND_DATA,
};

enum task_sm_signals {
    SIG_SM_REQ_WIFI_INFO = 0x01,
    SIG_SM_RES_WIFI_INFO,

    SIG_SM_REQ_WIFI_STATUS,
    SIG_SM_RES_WIFI_STATUS,
    SIG_SM_REQ_WIFI_RECONNECT,
    SIG_SM_REQ_WIFI_RECHANGE,

    SIG_SM_RES_WIFI_CONNECTED,
    SIG_SM_RES_WIFI_DISCONNECTED,

    SIG_SM_WAITING_CONNECT,
};

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */