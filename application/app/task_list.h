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

#define TASK_POLLING_DISABLE         (0x00)
#define TASK_POLLING_ENABLE          (0x01)

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

/* for enable polling with system tick */
extern uint8_t task_polling_status;

/* application task table */
extern task_t app_task_table[];

#ifdef __cplusplus
}
#endif

#endif /* __TASK_LIST_H__ */