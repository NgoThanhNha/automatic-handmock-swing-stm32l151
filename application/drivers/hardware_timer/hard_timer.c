/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "hard_timer.h"

#include "stm32l1xx_rcc.h"
#include "io_cfg.h"

volatile uint32_t system_tick_delay_counter = 0;

void systick_init(void) {
    SystemCoreClockUpdate();
    if (SysTick_Config(SystemCoreClock / 1000)) { 
        while (1);
    }
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
}

void delay_ms(uint32_t milliseconds) {
    uint32_t start_tick = system_tick_delay_counter;
    while ((system_tick_delay_counter - start_tick) < milliseconds);
    system_tick_delay_counter = 0;
}
