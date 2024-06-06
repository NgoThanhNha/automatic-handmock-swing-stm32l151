/**
 ******************************************************************************
 * @author: Nark
 * @date:   06/06/2024
 ******************************************************************************
**/

#ifndef __TASK_SM_H__
#define __TASK_SM_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

extern void task_sm_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __TASK_SM_H__ */