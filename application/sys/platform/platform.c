/**
 ******************************************************************************
 * @author: Nark
 * @date:   02/05/2024
 ******************************************************************************
**/

#include "platform.h"

#include "stm32l1xx.h"
#include "core_cm3.h"
#include "core_cmFunc.h"

#include "console.h"
#include "io_cfg.h"

void enable_interrupts() {
	__enable_irq();
}

void disable_interrupts() {
	__disable_irq();
}

void sys_ctrl_delay_ms(volatile uint32_t count) {
    __IO uint32_t currentTicks = SysTick->VAL;

    /* number of ticks per millisecond */
    const uint32_t tickPerMs = SysTick->LOAD + 1;

    /* number of ticks to count */
    const uint32_t nbTicks = ((count - ((count > 0) ? 1 : 0)) * tickPerMs);

    /* number of elapsed ticks */
    uint32_t elapsedTicks = 0;
    __IO uint32_t oldTicks = currentTicks;
    do {
        currentTicks = SysTick->VAL;
        elapsedTicks += (oldTicks < currentTicks) ? tickPerMs + oldTicks - currentTicks :
                                                    oldTicks - currentTicks;
        oldTicks = currentTicks;
    } while (nbTicks > elapsedTicks);
}

void fatal_error(const char* fatal_info, uint8_t fatal_id) {
    #if defined(RELEASE_EN)
        SYS_PRINT("\n");
        SYS_PRINT("************************ FATAL_ERROR ************************\n");
        SYS_PRINT("[FATAL_TYPE]: %s -> [FATAL_ID]: 0x%02X\n", fatal_info, fatal_id);
        SYS_PRINT("\n");
        NVIC_SystemReset();
    #else 
        disable_interrupts();
        SYS_PRINT("\n");
        SYS_PRINT("************************ FATAL_ERROR ************************\n");
        SYS_PRINT("[FATAL_TYPE]: %s -> [FATAL_ID]: 0x%02X\n", fatal_info, fatal_id);
        SYS_PRINT("\n");
        while (1) {
            led_life_on();
            sys_ctrl_delay_ms(100);
            led_life_off();
            sys_ctrl_delay_ms(100); 
        }
    #endif
}