/**
 ******************************************************************************
 * @author: Nark
 * @date:   07/06/2024
 ******************************************************************************
**/

#ifndef __SCREEN_NETWORK_H__
#define __SCREEN_NETWORK_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

enum wifi_status {
    WL_STATE_DISCONNECTED = 0x01,
    WL_STATE_CONNECTED,
    WL_STATE_RECONNECTING,
    WL_STATE_RECHANGING,
};

typedef struct {
    char wifi_ssid[30];
    char wifi_password[30];
} screen_network_info_t;

extern void screen_network_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_NETWORK_H__ */