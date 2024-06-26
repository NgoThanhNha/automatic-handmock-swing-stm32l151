/**
 ******************************************************************************
 * @author: Nark
 * @date:   03/06/2024
 ******************************************************************************
**/

#ifndef __DFPLAYER_H__
#define __DFPLAYER_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern void dfplayer_init();
extern void dfplayer_play();
extern void dfplayer_play_track(uint16_t num);
extern void dfplayer_play_next();
extern void dfplayer_play_prev();
extern void dfplayer_set_volume(uint16_t volume);
extern void dfplayer_enable_loop();
extern void dfplayer_disable_loop();
extern void dfplayer_pause();
extern void dfplayer_stop();

#ifdef __cplusplus
}
#endif

#endif /* __DFPLAYER_H__ */
