/**
 ******************************************************************************
 * @author: Nark
 * @date:   19/05/2024
 ******************************************************************************
**/

#ifndef __SCREEN_MAIN_H__
#define __SCREEN_MAIN_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define MAIN_INFO_MOTOR_SPEED_LEVEL_1          (0x01)
#define MAIN_INFO_MOTOR_SPEED_LEVEL_2          (0x02)
#define MAIN_INFO_MOTOR_SPEED_LEVEL_3          (0x03)

#define VELOCITY_SET_LEVEL_1                   (5000.0)
#define VELOCITY_SET_LEVEL_2                   (7000.0)
#define VELOCITY_SET_LEVEL_3                   (12000.0)

typedef struct {
    uint8_t speed = 2;
    uint8_t weight;
    uint8_t wifi_status;
    uint8_t cursor_select;
} screen_main_info_t;

extern screen_main_info_t main_screen_info;
extern void screen_main_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_MAIN_H__ */