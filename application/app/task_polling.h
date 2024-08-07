/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __TASK_POLLING_H__
#define __TASK_POLLING_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>

extern uint8_t task_polling_status;
extern void task_polling_handler();

#ifdef __cplusplus
}
#endif

#endif /* __TASK_POLLING_H__ */