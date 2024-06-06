/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/06/2024
 ******************************************************************************
**/

#include "task_safety.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"

#include "console.h"
#include "platform.h"
#include "hard_timer.h"

#include "ina219.h"

#include "app.h"
#include "task_list.h"
#include "task_polling.h"

safety_attr_t safety;

uint8_t polling_get_current_state = POLLING_GET_CURRENT_ENABLE;
void polling_checking_current();

void task_safety_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_CHECK_MOTOR_CURRENT:
        if (safety.motor_current < CURRENT_NOLOAD) {
            safety.check_noload++;
            if (safety.check_noload == NOLOAD_TIME_STOP) {
                polling_get_current_state = POLLING_GET_CURRENT_DISABLE;
                timer_remove(TASK_PID_ID, SIG_PID_RUN);
                PWM_GENERATION(0);
                APP_PRINT("[MOTOR] NO LOAD\n");
                APP_PRINT("[MOTOR] Stoped!\n");
            }
        }
        else {
            safety.check_noload = 0;
        }

        /* check overload */
        if (safety.motor_current > CURRENT_OVERLOAD) {
            safety.check_overload++;
            if (safety.check_overload == OVERLOAD_TIME_STOP) {
                polling_get_current_state = POLLING_GET_CURRENT_DISABLE;
                timer_remove(TASK_PID_ID, SIG_PID_RUN);
                PWM_GENERATION(0);
                APP_PRINT("[MOTOR] OVERLOAD\n");
                APP_PRINT("[MOTOR] Stoped!\n");
            }
        }
        else {
            safety.check_overload = 0;
        }
        break;
    
    default:
        break;
    }
}

void polling_checking_current() {
    static uint16_t polling_counter;
    if (polling_get_current_state == POLLING_GET_CURRENT_ENABLE) {
        if (polling_counter == GET_CURRENT_POLLING_PERIOD) {
            polling_counter = 0;
            safety.motor_current = ina219_read_current();
            task_post_pure_msg(TASK_SAFETY_ID, SIG_CHECK_MOTOR_CURRENT);
        }
        else {
            polling_counter++;
        }
    }
}