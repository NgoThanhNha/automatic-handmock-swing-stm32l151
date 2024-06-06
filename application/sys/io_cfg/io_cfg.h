/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#ifndef __IO_CFG_H__
#define __IO_CFG_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>

/*-----------------------------------------------------------------*/
/*                        led life pin map                         */ 
/*-----------------------------------------------------------------*/
#define LED_LIFE_IO_PIN                 (GPIO_Pin_13)
#define LED_LIFE_IO_PORT                (GPIOC)
#define LED_LIFE_IO_CLOCK               (RCC_AHBPeriph_GPIOC)

/*-----------------------------------------------------------------*/
/*                         usart1 pin map                          */
/*-----------------------------------------------------------------*/
#define CONSOLE_GPIO_PORT               (GPIOA)
#define CONSOLE_GPIO_CLOCK              (RCC_AHBPeriph_GPIOA)
#define CONSOLE_USART_CLOCK             (RCC_APB2Periph_USART1)

#define CONSOLE_TX_PIN                  (GPIO_Pin_9)
#define CONSOLE_RX_PIN                  (GPIO_Pin_10)
#define CONSOLE_TX_PIN_SOURCE           (GPIO_PinSource9)
#define CONSOLE_RX_PIN_SOURCE           (GPIO_PinSource10)

#define CONSOLE_USART                   (USART1)
#define CONSOLE_GPIO_AF                 (GPIO_AF_USART1)
#define CONSOLE_SPEED                   (115200)
#define CONSOLE_INTERRUPT               (USART1_IRQn)

/*-----------------------------------------------------------------*/
/*                   esplink - usart2 io pin map                   */
/*-----------------------------------------------------------------*/
#define ESP8266_LINK_GPIO_PORT          (GPIOA)
#define ESP8266_LINK_GPIO_CLOCK         (RCC_AHBPeriph_GPIOA)
#define ESP8266_LINK_USART_CLOCK        (RCC_APB1Periph_USART2)

#define ESP8266_LINK_TX_PIN             (GPIO_Pin_2)
#define ESP8266_LINK_RX_PIN             (GPIO_Pin_3)
#define ESP8266_LINK_TX_PIN_SOURCE      (GPIO_PinSource2)
#define ESP8266_LINK_RX_PIN_SOURCE      (GPIO_PinSource3)

#define ESP8266_LINK_USART              (USART2)
#define ESP8266_LINK_GPIO_AF            (GPIO_AF_USART2)
#define ESP8266_LINK_USART_SPEED        (115200)
#define ESP8266_LINK_INTERRUPT          (USART2_IRQn)

/*-----------------------------------------------------------------*/
/*                   dfplayer usart3 io pin map                    */
/*-----------------------------------------------------------------*/
#define DFPLAYER_GPIO_PORT               (GPIOB)
#define DFPLAYER_GPIO_CLOCK              (RCC_AHBPeriph_GPIOB)
#define DFPLAYER_USART_CLOCK             (RCC_APB1Periph_USART3)

#define DFPLAYER_TX_PIN                  (GPIO_Pin_10)
#define DFPLAYER_RX_PIN                  (GPIO_Pin_11)
#define DFPLAYER_TX_PIN_SOURCE           (GPIO_PinSource10)
#define DFPLAYER_RX_PIN_SOURCE           (GPIO_PinSource11)

#define DFPLAYER_USART                   (USART3)
#define DFPLAYER_GPIO_AF                 (GPIO_AF_USART3)
#define DFPLAYER_USART_SPEED             (9600)
#define DFPLAYER_INTERRUPT               (USART3_IRQn)

/*-----------------------------------------------------------------*/
/*                          l298n pin map                          */
/*-----------------------------------------------------------------*/
#define L298_TIMER                      (TIM3)
#define L298_TIMER_CLOCK_SOURCE         (RCC_APB1Periph_TIM3)
#define L298_GPIO_CLOCK_SOURCE          (RCC_AHBPeriph_GPIOB)

#define L298_GPIO_PORT                  (GPIOB)
#define L298_GPIO_PIN                   (GPIO_Pin_0)
#define L298_GPIO_PIN_SOURCE            (GPIO_PinSource0)
#define L298_GPIO_AF                    (GPIO_AF_TIM3)


#define L298_DIR_IO_PORT                (GPIOB)
#define L298_DIR_IO_CLOCK               (RCC_AHBPeriph_GPIOB)
#define L298_IN1_IO_PIN                 (GPIO_Pin_1)
#define L298_IN2_IO_PIN                 (GPIO_Pin_12)

/*-----------------------------------------------------------------*/
/*                       st7789 io pin map                         */
/*-----------------------------------------------------------------*/
#define ST7789_SPI                      (SPI1)
#define ST7789_SPI_CLOCK                (RCC_APB2Periph_SPI1)
#define ST7789_IO_PORT                  (GPIOA)
#define ST7789_IO_CLOCK                 (RCC_AHBPeriph_GPIOA)

#define ST7789_SCK_IO_PIN               (GPIO_Pin_5)
#define ST7789_SDA_IO_PIN               (GPIO_Pin_7)
#define ST7789_SCK_IO_PIN_SOURCE        (GPIO_PinSource5)
#define ST7789_SDA_IO_PIN_SOURCE        (GPIO_PinSource7)

#define ST7789_DC_IO_PORT               (GPIOA)
#define ST7789_DC_IO_PIN                (GPIO_Pin_6)
#define ST7789_DC_IO_CLOCK              (RCC_AHBPeriph_GPIOA)

#define ST7789_CS_IO_PORT               (GPIOA)
#define ST7789_CS_IO_PIN                (GPIO_Pin_4)
#define ST7789_CS_IO_CLOCK              (RCC_AHBPeriph_GPIOA)

#define ST7789_RST_IO_PORT              (GPIOA)
#define ST7789_RST_IO_PIN               (GPIO_Pin_1)
#define ST7789_RST_IO_CLOCK             (RCC_AHBPeriph_GPIOA)

/*-----------------------------------------------------------------*/
/*                        encoder io pin map                       */
/*-----------------------------------------------------------------*/
#define ENCODER_PINA_IO_PIN             (GPIO_Pin_3)
#define ENCODER_PINA_IO_PORT            (GPIOB)
#define ENCODER_PINA_IO_CLOCK           (RCC_AHBPeriph_GPIOB)

#define ENCODER_PINA_PORT_SOURCE        (EXTI_PortSourceGPIOB)
#define ENCODER_PINA_PIN_SOURCE         (EXTI_PinSource3)
#define ENCODER_PINA_EXTI_LINE          (EXTI_Line3)
#define ENCODER_PINA_IRQ_CHANNEL        (EXTI3_IRQn)

#define ENCODER_PINB_IO_PIN             (GPIO_Pin_4)
#define ENCODER_PINB_IO_PORT            (GPIOB)
#define ENCODER_PINB_IO_CLOCK           (RCC_AHBPeriph_GPIOB)

#define ENCODER_PINB_PORT_SOURCE        (EXTI_PortSourceGPIOB)
#define ENCODER_PINB_PIN_SOURCE         (EXTI_PinSource4)
#define ENCODER_PINB_EXTI_LINE          (EXTI_Line4)
#define ENCODER_PINB_IRQ_CHANNEL        (EXTI4_IRQn)

/*-----------------------------------------------------------------*/
/*                         ina219 pin map                          */
/*-----------------------------------------------------------------*/
#define INA219_GPIO_PORT                (GPIOB)
#define INA219_GPIO_CLOCK               (RCC_AHBPeriph_GPIOB)
#define INA219_SDA_PIN                  (GPIO_Pin_7)
#define INA219_SCL_PIN                  (GPIO_Pin_6)

#define INA219_SDA_PIN_AF               (GPIO_PinSource7)
#define INA219_SCL_PIN_AF               (GPIO_PinSource6)
#define INA219_GPIO_AF                  (GPIO_AF_I2C1)

#define INA219_SYSCFG_CLOCK             (RCC_APB2Periph_SYSCFG)
#define INA219_I2C                      (I2C1)
#define INA219_I2C_CLOCK_SOURCE         (RCC_APB1Periph_I2C1)

/*-----------------------------------------------------------------*/
/*                         buttons pin map                         */ 
/*-----------------------------------------------------------------*/
#define BUTTON_UP_IO_PIN                (GPIO_Pin_9)
#define BUTTON_UP_IO_PORT               (GPIOB)
#define BUTTON_UP_IO_CLOCK              (RCC_AHBPeriph_GPIOB)

#define BUTTON_DOWN_IO_PIN              (GPIO_Pin_8)
#define BUTTON_DOWN_IO_PORT             (GPIOB)
#define BUTTON_DOWN_IO_CLOCK            (RCC_AHBPeriph_GPIOB)

#define BUTTON_MODE_IO_PIN              (GPIO_Pin_5)
#define BUTTON_MODE_IO_PORT             (GPIOB)
#define BUTTON_MODE_IO_CLOCK            (RCC_AHBPeriph_GPIOB)

/* led life functions */
extern void led_life_on();
extern void led_life_off();

/* button functions */
extern uint8_t button_up_read();
extern uint8_t button_down_read();
extern uint8_t button_mode_read();

/* usart functions */
extern void usart1_init();
extern void usart1_put_char(uint8_t c);
extern void usart2_init();
extern void usart2_put_char(uint8_t c);
extern void usart3_init();
extern void usart3_put_char(uint8_t c);
extern void usart3_put_chars(uint8_t* str, uint16_t len);

/* spi1 functions */
extern void spi1_send_data(uint8_t data);
extern void spi_send_dma(uint8_t* buffer_send, uint32_t length);

/* st7789 pin io functions */
extern void st7789_cs_write_pin_high();
extern void st7789_cs_write_pin_low();

extern void st7789_dc_write_pin_high();
extern void st7789_dc_write_pin_low();

extern void st7789_rst_write_pin_high();
extern void st7789_rst_write_pin_low();

/* i2c init */
extern int i2c_read(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length);
extern int i2c_write(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length);

/* pwm functions */
#define PWM_GENERATION(CCR_SET)     pwm_set_duty_cycle(CCR_SET)
extern void pwm_set_duty_cycle(uint32_t ccr_set);

/* io initialize */
extern void io_init();

#ifdef __cplusplus
}
#endif

#endif /* __IO_CFG_H__ */