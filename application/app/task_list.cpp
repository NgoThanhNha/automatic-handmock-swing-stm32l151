/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "task_list.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "console.h"

#include "app.h"
#include "task_pid.h"
#include "task_display.h"
#include "task_safety.h"
#include "task_sm.h"
#include "link_phy.h"

task_t app_task_table[] = {
    /*************************************************************************/
	/* SYSTEM TASKS */
	/*************************************************************************/
    {TASK_TIMER_TICK_ID,              task_timer_handler},

    /*************************************************************************/
	/* APP TASKS */
	/*************************************************************************/
    {TASK_PID_ID,                     task_pid_handler},
    {TASK_DISPLAY_ID,                 task_display_handler},
    {TASK_SAFETY_ID,                  task_safety_handler},
    {TASK_SM_ID,                      task_sm_handler},
    {LINK_PHY_ID,                     link_phy_handler},

    /*************************************************************************/
	/* END OF TABLE */
	/*************************************************************************/
    {STK_TASK_EOT_ID,                 (pf_task)0},
};