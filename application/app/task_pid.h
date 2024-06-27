/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __TASK_PID_H__
#define __TASK_PID_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define PID_INTERVAL            (20)
#define TIMER_PERIOD_MAX        (1332.0)

#define PID_DISABLE             (0x00)
#define PID_ENABLE              (0x01)

typedef struct {
    uint8_t status;
    float kp;
    float kd;
    float ki;
    float current_velocity;
    float velocity_set;
    float prev_error;
    float prev_ui;
    float sampling_time;
} pid_attr_t;

extern pid_attr_t pid_attribute;
extern void task_pid_handler(stk_msg_t* msg);
extern void pid_set(float speed_set);
extern void polling_pid();
extern float get_duty_cycle();
extern void pid_enable();
extern void pid_disable();

#ifdef __cplusplus
}
#endif

#endif /* __TASK_PID_H__ */