/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __TASK_DISPLAY_H__
#define __TASK_DISPLAY_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#include "screen_manager.h"

extern scr_mng_t app_screen;
extern void task_display_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __TASK_DISPLAY_H_ */