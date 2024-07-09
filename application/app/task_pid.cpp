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
#include "screen_main.h"

/* for pid calculate */
uint16_t get_encoder_counter;
uint32_t pwm_to_motor;
float voltage_for_dbg;
pid_attr_t pid_attribute;

static float pid_run(float velocity_set);
void pid_enable();
void pid_disable();

void task_pid_handler(stk_msg_t* msg) {
    switch (msg->sig) {
    case SIG_PID_INIT:
        pid_attribute.status = PID_ENABLE;
        pid_attribute.kp = 1.023;
        pid_attribute.kd = 0.575;
        pid_attribute.ki = 3.167;
        pid_attribute.velocity_set = VELOCITY_SET_LEVEL_2;
        main_screen_info.speed = MAIN_INFO_MOTOR_SPEED_LEVEL_2;
        pid_attribute.current_velocity = 0;
        pid_attribute.prev_error = 0;
        pid_attribute.prev_ui = 0;
        pid_attribute.sampling_time = (PID_INTERVAL) / 1000.0;
        break;

    case SIG_PRINT_VELOCITY:
        APP_DBG("Current motor speed: %.2f\n", pid_attribute.current_velocity);
        break;
    
    default:
        break;
    }
}

float pid_run(float velocity_set) {
    /* error */
    float error_velocity = velocity_set - pid_attribute.current_velocity;

    /* proportional */
    float up = pid_attribute.kp * error_velocity;

    /* derivative */
    float ud = pid_attribute.kd * ((error_velocity - pid_attribute.prev_error) / pid_attribute.sampling_time);

    /* integral */
    float ui = pid_attribute.prev_ui + (pid_attribute.ki * error_velocity * pid_attribute.sampling_time);

    /* pid value */
    
    float pid_calculated = (up + ud + ui);
    if (ui>1332){
        ui=1332;
    }
    else if(ui<-1332){
        ui=-1332;
    }

    pid_attribute.prev_ui = ui;

    /* assign current error to previous error */
    pid_attribute.prev_error = error_velocity;

    /* generate to output */
    if (pid_calculated < 0) {
        pid_calculated = 0;
    }
    else if (pid_calculated >= TIMER_PERIOD_MAX) {
        pid_calculated = TIMER_PERIOD_MAX - 1;
    }
    return pid_calculated;
}

void pid_set(float speed_set, float kp_set, float ki_set, float kd_set) {
    pid_attribute.velocity_set = speed_set;
    pid_attribute.kp = kp_set;
    pid_attribute.ki = ki_set;
    pid_attribute.kd = kd_set;
}

void polling_pid() {
    static uint16_t polling_counter;
    if (pid_attribute.status == PID_ENABLE) {
        if (polling_counter == PID_INTERVAL) {
            polling_counter = 0;

            /* get current velocity */
            ENTRY_CRITICAL();
            get_encoder_counter = get_exti_value();
            pid_attribute.current_velocity = (float)((get_encoder_counter * 50.0) / 44.0) * 60.0;
            reset_encoder_value();
            EXIT_CRITICAL();

            /* generate the pwm value to driver */
            pwm_to_motor = (uint32_t)pid_run(pid_attribute.velocity_set);
            PWM_GENERATION(pwm_to_motor);
        }
        else {
            polling_counter++;
        }
    }
    else {
        if (polling_counter == PID_INTERVAL) {
            polling_counter = 0;

            /* get current velocity */
            ENTRY_CRITICAL();
            get_encoder_counter = get_exti_value();
            pid_attribute.current_velocity = (float)((get_encoder_counter * 50.0) / 44.0) * 60.0;
            reset_encoder_value();
            EXIT_CRITICAL();
            PWM_GENERATION((uint32_t)((voltage_for_dbg / 12.0) * 1332));
        }
        else {
            polling_counter++;
        }
    }
}

float get_duty_cycle() {
    return (pwm_to_motor / (TIMER_PERIOD_MAX));
}

void pid_enable() {
    pid_attribute.status = PID_ENABLE;
}

void pid_disable() {
    pid_attribute.status = PID_DISABLE;
    pid_attribute.velocity_set = 0;
    pwm_to_motor = 0;
    PWM_GENERATION(pwm_to_motor);
    timer_remove(TASK_SM_ID, SIG_SM_REQ_WIFI_STATUS);
}