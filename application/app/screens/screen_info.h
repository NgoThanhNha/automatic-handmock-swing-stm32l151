/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/06/2024
 ******************************************************************************
**/

#ifndef __SCREEN_INFO_H__
#define __SCREEN_INFO_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

extern void screen_info_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_INFO_H__ */