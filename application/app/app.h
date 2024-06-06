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
    SIG_PID_RUN,

    /* TASK DISPLAY */
    SIG_SCREEN_TRANS,
    SIG_SCREEN_ANIMATION,
    SIG_DISPLAY_IDLE_SCREEN_UPDATE,
    
    SIG_BUTTON_UP_PRESSED,
    SIG_BUTTON_DOWN_PRESSED,
    SIG_BUTTON_MODE_PRESSED,
    SIG_BUTTON_MODE_LONG_PRESSED,

    /* TASK CHECK */
    SIG_CHECK_MOTOR_CURRENT,

    /* ESP8266 UART LINK */
    SIG_LINK_PHY_GET_BUFF,
    SIG_LINK_PHY_GET_MSG_RES,
    SIG_LINK_PHY_SEND_DATA,
};

enum task_sm_signals {
    SIG_SM_REQ_CHECK_WIFI_CONNECT,
    SIG_SM_RES_WIFI_CONNECTED,
    SIG_SM_RES_WIFI_DISCONNECTED,
    SIG_SM_RES_WIFI_CONFIGURATED,
};

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */