/**
 ******************************************************************************
 * @author: Nark
 * @date:   14/06/2024
 ******************************************************************************
**/

#ifndef __SCREEN_TRACK_H__
#define __SCREEN_TRACK_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>

#include "message.h"

#define MUSIC_OFF               (0x00)
#define MUSIC_ON                (0x01)

typedef struct {
    uint8_t music_status;
    uint8_t volume;
} screen_track_info_t;

extern screen_track_info_t screen_track_info;
extern void screen_track_handler(stk_msg_t* msg);

#ifdef __cplusplus
}
#endif

#endif /* __SCREETRACK_H__ */