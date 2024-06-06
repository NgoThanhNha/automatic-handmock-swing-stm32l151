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

typedef struct {
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

#ifdef __cplusplus
}
#endif

#endif /* __TASK_PID_H__ */