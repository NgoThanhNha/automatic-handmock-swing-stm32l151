/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "stm32l1xx.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_usart.h"
#include "system_irq.h"
#include "io_cfg.h"

#include "timer.h"

#include "platform.h"
#include "console.h"
#include "hard_timer.h"
#include "buzzer.h"

#include "app.h"
#include "link_phy.h"
#include "task_polling.h"
#include "task_list.h"

volatile uint32_t exti_counter;

void default_handler() {
	FATAL("SYSTEM", 0x01);
}

void nmi_handler() {
	FATAL("SYSTEM", 0x02);
}

void hard_fault_handler() {
	FATAL("SYSTEM", 0x03);
}

void mem_manage_handler() {
	FATAL("SYSTEM", 0x04);
}

void bus_fault_handler() {
	FATAL("SYSTEM", 0x05);
}

void usage_fault_handler() {
	FATAL("SYSTEM", 0x06);
}

void system_tick_handler() {
	timer_tick(1);
	system_tick_delay_counter++;
	task_polling_handler();
}

void exti3_irq_handler() {
	if(EXTI_GetITStatus(EXTI_Line3) != RESET) {
		ENTRY_CRITICAL();
		exti_counter++;
		EXIT_CRITICAL();
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

void exti4_irq_handler() {
	if(EXTI_GetITStatus(EXTI_Line4) != RESET) {
		ENTRY_CRITICAL();
		exti_counter++;
		EXIT_CRITICAL();
		EXTI_ClearITPendingBit(EXTI_Line4);
	}
}

uint16_t get_exti_value() {
	return exti_counter;
}

void reset_encoder_value() {
	ENTRY_CRITICAL();
	exti_counter = 0;
	EXIT_CRITICAL();
}

void usart2_irq_handler() {
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		/* clear receive flag it*/
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);

		/* put to buffer */
		volatile uint8_t c;
		c = (uint8_t)USART_ReceiveData(USART2);
		usart2_get_char(c);
	}
}