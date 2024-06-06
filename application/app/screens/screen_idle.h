/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __SCREEN_IDLE_H_
#define __SCREEN_IDLE_H_

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define SCREEN_WIDTH                        (320)
#define SCREEN_HEIGHT                       (172)
#define NUM_BALL_MAX                        (5)

typedef struct {
    int x, y, axis_x, axis_y, radius, slope;
} ball_t;

extern uint8_t screen_idle_polling_state;
extern void screen_idle_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_IDLE_H_ */