/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/06/2024
 ******************************************************************************
**/

#ifndef __TASK_SAFETY_H__
#define __TASK_SAFETY_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define CURRENT_OVERLOAD                (300.0)
#define CURRENT_NOLOAD                  (200.0)
#define NOLOAD_TIME_STOP                (30)
#define OVERLOAD_TIME_STOP              (10)

#define POLLING_GET_CURRENT_DISABLE         (0x00)
#define POLLING_GET_CURRENT_ENABLE          (0x01)
#define GET_CURRENT_POLLING_PERIOD          (1000)

typedef struct {
    float motor_current;
    uint8_t check_noload;
    uint8_t check_overload;
} safety_attr_t;

extern void task_safety_handler(stk_msg_t* msg);
extern void polling_checking_current();

#ifdef __cplusplus
}
#endif

#endif /* __TASK_SAFETY_H__ */