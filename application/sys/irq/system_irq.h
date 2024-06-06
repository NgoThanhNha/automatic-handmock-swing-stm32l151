
/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#ifndef __SYSTEM_IRQ_H__
#define __SYSTEM_IRQ_H__

#ifdef __cplusplus
 extern "C" {
#endif 

/* system functions */
extern void default_handler();
extern void nmi_handler();
extern void hard_fault_handler();
extern void mem_manage_handler();
extern void bus_fault_handler();
extern void usage_fault_handler();
extern void svc_handler();
extern void pendsv_handler();
extern void system_tick_handler();

/* external interrupt functions */
extern void exti3_irq_handler();
extern void exti4_irq_handler();
extern void usart2_irq_handler();

/* encoder functions */
extern uint16_t get_exti_value();
extern void reset_encoder_value();

#ifdef __cplusplus
}
#endif

#endif /* __SYSTEM_IRQ_H__ */
