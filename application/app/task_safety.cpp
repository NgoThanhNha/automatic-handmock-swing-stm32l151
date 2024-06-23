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

#include "screen_main.h"

safety_attr_t safety;
float buffer_current[10];
float mass_estimated;
static uint8_t current_save_index;
static uint8_t polling_get_current_state = POLLING_GET_CURRENT_ENABLE;

void polling_checking_current();
static float update_current(float new_current);
static float estimate_mass(float motor_current);

void task_safety_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_CHECK_CURRENT_WARNING:
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
    
    case SIG_MASS_CALCULATE:
        APP_DBG("Mass estimated: %d kg\n", main_screen_info.weight);
        break;

    default:
        break;
    }
}

void polling_checking_current() {
    static uint16_t polling_counter;
    if (polling_get_current_state == POLLING_GET_CURRENT_ENABLE) {
        switch (polling_counter) {
        case GET_CURRENT_POLLING_PERIOD:
            safety.motor_current = update_current(ina219_read_current());
            mass_estimated = estimate_mass((safety.motor_current) / 1000.0);
            main_screen_info.weight = (uint8_t)(mass_estimated);
            break;
        
        case GET_VOLTAGE_POLLING_PERIOD:
            polling_counter = 0;
            safety.bus_voltage = ina219_read_bus_voltage();
            // task_post_pure_msg(TASK_SAFETY_ID, SIG_CHECK_CURRENT_WARNING);
            break;

        default:
            break;
        }
        polling_counter++;
    }
}

float update_current(float new_current) {
    /* update new value */
    buffer_current[current_save_index] = new_current;
    current_save_index++;
    
    if (current_save_index >= 5) {
        current_save_index = 0;
    }

    /* current average calculate */
    float sum = 0.0;
    for (int i = 0; i < 5; i++) {
        sum += buffer_current[i];
    }
    float average = sum / 5;

    return average;
}

float estimate_mass(float motor_current) {
    float torque = K_T * (motor_current - ESTIMATE_CURRENT_NOLOAD);
    float force = torque / SHAFT_RADIUS;
    float mass = force / g;
    return mass;
}