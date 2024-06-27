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

#define CURRENT_NO_LOAD                     (120)
#define NOLOAD_TIME_STOP                    (30)
#define OVERLOAD_TIME_STOP                  (10)

/* define for power sensing polling */
#define POLLING_GET_CURRENT_DISABLE         (0x00)
#define POLLING_GET_CURRENT_ENABLE          (0x01)

#define GET_CURRENT_POLLING_PERIOD          (50)
#define GET_VOLTAGE_POLLING_PERIOD          (150)
#define GET_POWER_POLLING_PERIOD            (1000)

/* define for estimate */
#define K_T                                 (1.0527)
#define ESTIMATE_CURRENT_NOLOAD             (0.13)
#define SHAFT_RADIUS                        (0.003)   
#define g                                   (9.81)

/* 
define current for change setpoint
    50 - 104: no load
    105 - 125: 7100
    180 - 205: 6900
    245 - 300: 6700
    > 320: OVERLOAD
*/
#define CURRENT_POINT_1                     (50)  
#define CURRENT_POINT_2                     (104)
#define CURRENT_POINT_3                     (105) 
#define CURRENT_POINT_4                     (125) 
#define CURRENT_POINT_5                     (180)
#define CURRENT_POINT_6                     (205)
#define CURRENT_POINT_7                     (245)
#define CURRENT_POINT_8                     (300)

typedef struct {
    float bus_voltage;
    float motor_voltage;
    float motor_current;
    float power;
    uint8_t check_noload;
    uint8_t check_overload;
} safety_attr_t;

extern safety_attr_t safety;
extern void task_safety_handler(stk_msg_t* msg);

/* polling function prototypes */
extern void polling_checking_current();
extern void polling_checking_voltage();
extern void polling_checking_power();

#ifdef __cplusplus
}
#endif

#endif /* __TASK_SAFETY_H__ */