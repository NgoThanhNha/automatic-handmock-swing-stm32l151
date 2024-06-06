/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "task_display.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"
#include "screen_manager.h"

#include "io_cfg.h"
#include "app.h"
#include "task_list.h"

scr_mng_t app_screen;

void task_display_handler(stk_msg_t* msg) {
    screen_mng_dispatch(msg);
}