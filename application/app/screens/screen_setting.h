/**
 ******************************************************************************
 * @author: Nark
 * @date:   04/06/2024
 ******************************************************************************
**/

#ifndef __SCREEN_SETTING_H__
#define __SCREEN_SETTING_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

typedef struct {
    uint8_t cursor_select;
} screen_setting_info_t;

extern void screen_setting_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREEN_SETTING_H__ */