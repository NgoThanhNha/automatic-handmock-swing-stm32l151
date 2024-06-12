/**
 ******************************************************************************
 * @author: Nark
 * @date:   08/06/2024
 ******************************************************************************
**/

#ifndef __SCREEN_POWER_H__
#define __SCREEN_POWER_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

extern void screen_power_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_POWER_H__ */