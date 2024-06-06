/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __HARD_TIMER_H__
#define __HARD_TIMER_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

extern volatile uint32_t system_tick_delay_counter;
extern void systick_init(void);
extern void delay_ms(uint32_t milliseconds);

#ifdef __cplusplus
}
#endif

#endif /* __HARD_TIMER_H__ */