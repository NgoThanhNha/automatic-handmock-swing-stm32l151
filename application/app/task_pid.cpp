/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "task_pid.h"

#include "stk.h"
#include "message.h"
#include "timer.h"

#include "io_cfg.h"
#include "system_irq.h"

#include "console.h"
#include "platform.h"
#include "screen_manager.h"

#include "ina219.h"

#include "app.h"
#include "task_list.h"

uint16_t get_encoder_counter;
uint32_t pwm_to_motor;
pid_attr_t pid_attribute;

float bus_voltage;
float shunt_voltage;
float motor_current;

static uint32_t pid_run(float velocity_set);

void task_pid_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_PID_INIT:
        pid_attribute.kp = 0.88498747483835;
        pid_attribute.kd = 0.00193091246061319;
        pid_attribute.ki = 0.5;
        pid_attribute.velocity_set = 10000;
        pid_attribute.current_velocity = 0;
        pid_attribute.prev_error = 0;
        pid_attribute.prev_ui = 0;
        pid_attribute.sampling_time = (PID_INTERVAL) / 1000.0;
        break;

    case SIG_VELOCITY_CALCULATE:
        break;

    case SIG_PID_RUN:
        /* get current velocity */
        ENTRY_CRITICAL();
        get_encoder_counter = get_exti_value();
        pid_attribute.current_velocity = (float)((get_encoder_counter * 50.0) / 44.0) * 60.0;
        reset_encoder_value();
        EXIT_CRITICAL();

        /* generate the pwm value to driver */
        pwm_to_motor = pid_run(pid_attribute.velocity_set);
        PWM_GENERATION(pwm_to_motor);
        break;

    case SIG_PRINT_VELOCITY:
        break;
    
    default:
        break;
    }
}

uint32_t pid_run(float velocity_set) {
    /* error */
    float error_velocity = velocity_set - pid_attribute.current_velocity;

    /* proportional */
    float up = pid_attribute.kp * error_velocity;

    /* derivative */
    float ud = pid_attribute.kd * ((error_velocity - pid_attribute.prev_error) / pid_attribute.sampling_time);

    /* integral */
    float ui = pid_attribute.prev_ui + (pid_attribute.ki * error_velocity * pid_attribute.sampling_time);

    /* pid value */
    uint32_t pid_calculated = (uint32_t)(up + ud + ui);
    pid_attribute.prev_ui = ui;

    /* assign current error to previous error */
    pid_attribute.prev_error = error_velocity;

    /* generate to output */
    if (pid_calculated < 0) {
        pid_calculated = 0;
    }
    else if (pid_calculated >= 0xFFFFFFFF) {
        pid_calculated = 0xFFFFFFFF;
    }
    return pid_calculated;
}

void pid_set(float speed_set) {
    pid_attribute.velocity_set = speed_set;
}