/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#ifdef __cplusplus
 extern "C" {
#endif 

#include <stdint.h>
#include "stk.h"

enum {
    /* KERNEL TASKS */
    TASK_TIMER_TICK_ID,

    /* APP TASKS */
    TASK_PID_ID,
    TASK_DISPLAY_ID,
    TASK_SAFETY_ID,
    TASK_SM_ID,
    LINK_PHY_ID,

    /* END OF TABLE */
    STK_TASK_EOT_ID,
};

extern task_t app_task_table[];

#ifdef __cplusplus
}
#endif

#endif /* __TASK_LIST_H__ */