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
enum {
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

    /* TASK SM - MATER SLAVE */
    SIG_MSG_OUT_CHECK_WIFI_CONNECT,
    SIG_MSG_IN_WIFI_CONNECTED,
    SIG_MSG_IN_WIFI_DISCONNECTED,
    SIG_MSG_IN_WIFI_CONFIGURATED,

    /* TASK CHECK */
    SIG_CHECK_MOTOR_CURRENT,

    /* ESP8266 UART LINK */
    SIG_LINK_PHY_GET_BUFF,
    SIG_LINK_PHY_SEND_DATA,
    SIG_LINK_PHY_FW_MSG_OUT,
    SIG_LINK_PHY_GET_MSG_IN,
};

#ifdef __cplusplus
}
#endif

#endif /* __APP_H__ */