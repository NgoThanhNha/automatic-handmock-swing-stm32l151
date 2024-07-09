/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "stk_startup.h"

#include "stk.h"
#include "message.h"

#include "system_stm32l1xx.h"
#include "stm32l1xx.h"
#include "stm32l1xx_conf.h"
#include "core_cm3.h"

#include "app.h"
#include "io_cfg.h"
#include "system_irq.h"

#include "platform.h"
#include "console.h"

/* define the addresses of data and bss sections */
extern uint32_t _sidata, _sdata, _edata, _sbss, _ebss, _estack;
extern void (*__preinit_array_start[])();
extern void (*__preinit_array_end[])();
extern void (*__init_array_start[])();
extern void (*__init_array_end[])();

static void sys_banner();
static void sys_cfg_clock();

/* cortex-M processor non-fault exceptions */
void dg_monitor_handler() {
    default_handler();
}

void pendsv_handler() {
    default_handler();
}

void svc_handler() {
    default_handler();
}

/* reset handler */
void reset_handler(void) {
    /* call the system init function */
    SystemInit();

    uint32_t *src, *dest;

    /*------------------------------------------------------------------*/
    /*      copy the data segment initializers from flash to SRAM       */
    /*------------------------------------------------------------------*/
    /* pointer start address in flash */
    src = &_sidata;
    /* pointer start address in sram */
    dest = &_sdata;
    while (dest < &_edata) {
        *dest++ = *src++;
    }

    /* zero fill to .bss section */
    dest = &_sbss;
    while (dest < &_ebss) {
        *dest++ = 0;
    }

    volatile unsigned i, cnt;
    
	/* invoke all static constructors */
	cnt = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < cnt; i++)
		__preinit_array_start[i]();

	cnt = __init_array_end - __init_array_start;
	for (i = 0; i < cnt; i++)
		__init_array_start[i]();

	/* sys clock cfg */
	sys_cfg_clock();
	
    /* usart1 init */
	usart1_init();

    /* console init */
    console_init();

    /* system banner */
    sys_banner();
    
    /* go to the main application */
    main_app();
}

/* STM32F042 cortex-M0 processor exception vector table */
__attribute__((section(".isr_vector"))) void (*const g_pfnVectors[])(void) = {
		((void (*)())(uint32_t)&_estack),		//	The initial stack pointer
		reset_handler,							//	The reset handler
		nmi_handler,							//	The NMI handler
		hard_fault_handler,						//	The hard fault handler
		mem_manage_handler,						//	The MPU fault handler
		bus_fault_handler,						//	The bus fault handler
		usage_fault_handler,					//	The usage fault handler
		0,										//	Reserved
		0,										//	Reserved
		0,										//	Reserved
		0,										//	Reserved
		svc_handler,							//	SVCall handler
		dg_monitor_handler,						//	Debug monitor handler
		0,										//	Reserved
		pendsv_handler,							//	The PendSV handler
		system_tick_handler,					//	The SysTick handler

		/* external interrupts */
		default_handler,						//	Window Watchdog
		default_handler,						//	PVD through EXTI Line detect
		default_handler,						//	Tamper and Time Stamp
		default_handler,						//	RTC Wakeup
		default_handler,						//	FLASH
		default_handler,						//	RCC
		default_handler,						//	EXTI Line 0
		default_handler,						//	EXTI Line 1
		default_handler,						//	EXTI Line 2
		exti3_irq_handler,						//	EXTI Line 3
		exti4_irq_handler,						//	EXTI Line 4
		default_handler,						//	DMA1 Channel 1
		default_handler,						//	DMA1 Channel 2
		default_handler,						//	DMA1 Channel 3
		default_handler,						//	DMA1 Channel 4
		default_handler,						//	DMA1 Channel 5
		default_handler,						//	DMA1 Channel 6
		default_handler,						//	DMA1 Channel 7
		default_handler,						//	ADC1
		default_handler,						//	USB High Priority
		default_handler,						//	USB Low  Priority
		default_handler,						//	DAC
		default_handler,						//	COMP through EXTI Line
		default_handler,						//	EXTI Line 9..5
		default_handler,						//	LCD
		default_handler,						//	TIM9
		default_handler,						//	TIM10
		default_handler,						//	TIM11
		default_handler,						//	TIM2
		default_handler,						//	TIM3
		default_handler,						//	TIM4
		default_handler,						//	I2C1 Event
		default_handler,						//	I2C1 Error
		default_handler,						//	I2C2 Event
		default_handler,						//	I2C2 Error
		default_handler,						//	SPI1
		default_handler,						//	SPI2
		0,										//	USART1
		usart2_irq_handler,					    //	USART2
		0,										//	USART3
		default_handler,						//	EXTI Line 15..10
		default_handler,						//	RTC Alarm through EXTI Line
		default_handler,						//	USB FS Wakeup from suspend
		default_handler,						//	TIM6
		default_handler,					    //	TIM7
};

void sys_cfg_clock() {
    // Enable HSE (High Speed External) clock
    RCC_HSEConfig(RCC_HSE_ON);
    // Wait till HSE is ready
    while (RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);

    // Configure the PLL (Phase Locked Loop)
    // HSE=8MHz, PLL=32MHz (8 * 12 / 3)
    RCC_PLLConfig(RCC_PLLSource_HSE, RCC_PLLMul_12, RCC_PLLDiv_3); 
    RCC_PLLCmd(ENABLE);

    // Wait till PLL is ready
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

    // Select PLL as system clock source
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    // Wait till PLL is used as system clock source
    while (RCC_GetSYSCLKSource() != 0x0C);

    // Configure the HCLK, PCLK1, and PCLK2 clocks dividers
    RCC_HCLKConfig(RCC_SYSCLK_Div1);   // HCLK = SYSCLK = 32 MHz
    RCC_PCLK1Config(RCC_HCLK_Div2);    // PCLK1 = HCLK/2 = 16 MHz
    RCC_PCLK2Config(RCC_HCLK_Div1);    // PCLK2 = HCLK = 32 MHz

    // Enable the Clock Security System (CSS)
    RCC_ClockSecuritySystemCmd(ENABLE);
}

void sys_banner() {
    SYS_PRINT("\n");
    SYS_PRINT(" ___  ____  _  _ \n");
    SYS_PRINT("/ __)(_  _)( )/ )\n");
    SYS_PRINT("\\__ \\  )(  (   (\n");
    SYS_PRINT("(___/ (__) (_)\\_)\n");
    SYS_PRINT("\n");
    SYS_PRINT("Kernel version: %s\n", STK_VERSION);
}