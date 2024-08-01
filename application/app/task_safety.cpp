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
#include "task_pid.h"

#include "screen_main.h"

safety_attr_t safety;

/* for read motor current */
float buffer_current[40];
float buffer_max_current[3];
static uint8_t current_save_index;
static uint8_t current_max_index;
float sum = 0.0;
float max_motor_current;

/* estimate the weight */
float mass_estimated;

/* alternative functions */
static float estimate_mass(float motor_current);
static void update_current(float new_current);
static void change_setpoint(float motor_current);

void task_safety_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_CHECK_CURRENT_WARNING:
        if (safety.motor_current < CURRENT_NO_LOAD) {
            APP_PRINT("[TASK_SAFETY] CURRENT_NO_LOAD\n");
            safety.check_noload++;
            if (safety.check_noload == NOLOAD_TIME_STOP) {
                pid_disable();
                APP_PRINT("[MOTOR] NO LOAD\n");
                APP_PRINT("[MOTOR] Stoped!\n");
                timer_remove(TASK_SAFETY_ID, SIG_CHECK_CURRENT_WARNING);
            }
        }
        else {
            safety.check_noload = 0;
        }

        /* check overload */
        if (safety.motor_current > CURRENT_POINT_8) {
            safety.check_overload++;
            if (safety.check_overload == OVERLOAD_TIME_STOP) {
                pid_disable();
                APP_PRINT("[MOTOR] OVERLOAD\n");
                APP_PRINT("[MOTOR] Stoped!\n");
                timer_remove(TASK_SAFETY_ID, SIG_CHECK_CURRENT_WARNING);
            }
        }
        else {
            safety.check_overload = 0;
        }
        break;
    
    case SIG_MASS_CALCULATE:
        APP_DBG("Mass estimated: %d kg\n", main_screen_info.weight);
        break;

    case SIG_CHECK_MAX_CURRENT:
        APP_PRINT("[TASK_SAFETY] SIG_CHECK_MAX_CURRENT\n");
        max_motor_current = buffer_max_current[0];
        for (int i = 0; i < 3; i++) {
            if (buffer_current[i] > max_motor_current) {
                max_motor_current = buffer_current[i];
            }
        }
        break;  

    default:
        break;
    }
}

void polling_checking_current() {
    if (pid_attribute.status == PID_ENABLE) {
        static uint16_t polling_counter;
        if (polling_counter == GET_CURRENT_POLLING_PERIOD) {
            update_current(ina219_read_current());
            polling_counter = 0;
        }
        else {
            polling_counter++;
        } 
    }
}

void polling_checking_voltage() {
    static uint16_t polling_counter;
    if (polling_counter == GET_VOLTAGE_POLLING_PERIOD) {
        safety.bus_voltage = ina219_read_bus_voltage();
        float get_duty = get_duty_cycle();
        safety.motor_voltage = safety.bus_voltage * get_duty;
        polling_counter = 0;
    }
    else {
        polling_counter++;
    } 
}

void polling_checking_power() {
    static uint16_t polling_counter;
    if (polling_counter == GET_POWER_POLLING_PERIOD) {
        safety.power = ina219_read_power_mW();
        polling_counter = 0;
    }
    else {
        polling_counter++;
    } 
}

float estimate_mass(float motor_current) {
    float torque = K_T * (motor_current - ESTIMATE_CURRENT_NOLOAD);
    float force = torque / SHAFT_RADIUS;
    float mass = force / g;
    return mass;
}

void update_current(float new_current) {
    /* update new value */
    buffer_current[current_save_index] = new_current;
    current_save_index++;
    
    if (current_save_index >= 40) {
        ENTRY_CRITICAL();
        current_save_index = 0;

        /* current average calculate */
        float sum = 0.0;
        for (int i = 0; i < 40; i++) {
            sum += buffer_current[i];
        }
        float average = sum / 40;
        safety.motor_current = average;
        buffer_max_current[current_max_index] = average;
        current_max_index++;
        if (current_max_index == 3) {
            current_max_index = 0;
            task_post_pure_msg(TASK_SAFETY_ID, SIG_CHECK_MAX_CURRENT);
        }
        change_setpoint(safety.motor_current);
        EXIT_CRITICAL();
    }
}

void change_setpoint(float motor_current) {
    if (pid_attribute.status == PID_ENABLE) {
        if ((motor_current >= CURRENT_POINT_3) && (motor_current < CURRENT_POINT_4)) {
            pid_set(6800, 0.65139, 0.60269, 0.0024);
        }
        else if ((motor_current >= CURRENT_POINT_5) && (motor_current < CURRENT_POINT_6)) {
            pid_set(6800, 1.30278, 0.12035, 0.012);
        }
        else if ((motor_current >= CURRENT_POINT_7) && (motor_current < CURRENT_POINT_8)) {
            pid_set(6800, 1.30278, 0.12035, 0.012);
        }
    }
}