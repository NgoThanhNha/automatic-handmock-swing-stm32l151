/**
 ******************************************************************************
 * @author: Nark
 * @date:   29/03/2024
 ******************************************************************************
**/

#include "io_cfg.h"

#include "misc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_rcc.h"
#include "stm32l1xx_usart.h"
#include "stm32l1xx_spi.h"
#include "stm32l1xx_tim.h"
#include "stm32l1xx_exti.h"
#include "stm32l1xx_i2c.h"
#include "stm32l1xx_dma.h"
#include "stm32l1xx_syscfg.h"

#include "xprintf.h"

/* structure for init pwm timer */
TIM_TimeBaseInitTypeDef  L298_TimerInitStructure;
TIM_OCInitTypeDef  L298_OCInitStructure;
GPIO_InitTypeDef L298_GPIOInitStructure;

/* struct for i2c */
I2C_InitTypeDef  I2C_InitStructure;

void led_life_init() {
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(LED_LIFE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = LED_LIFE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(LED_LIFE_IO_PORT, &GPIO_InitStructure);
}

void led_life_on() {
	GPIO_SetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void led_life_off() {
	GPIO_ResetBits(LED_LIFE_IO_PORT, LED_LIFE_IO_PIN);
}

void usart1_init() {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* enable clocks */
	RCC_AHBPeriphClockCmd(CONSOLE_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(CONSOLE_USART_CLOCK, ENABLE);

	/* pin af config */
	GPIO_PinAFConfig(CONSOLE_GPIO_PORT, CONSOLE_TX_PIN_SOURCE, CONSOLE_GPIO_AF);
	GPIO_PinAFConfig(CONSOLE_GPIO_PORT, CONSOLE_RX_PIN_SOURCE, CONSOLE_GPIO_AF);

	/* gpio config */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = CONSOLE_TX_PIN;
	GPIO_Init(CONSOLE_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = CONSOLE_RX_PIN;
	GPIO_Init(CONSOLE_GPIO_PORT, &GPIO_InitStructure);

	/* usart1 config */
	USART_InitStructure.USART_BaudRate = CONSOLE_SPEED;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(CONSOLE_USART, &USART_InitStructure);

	/* enable the usart interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = CONSOLE_INTERRUPT;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(CONSOLE_USART, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(CONSOLE_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(CONSOLE_USART, USART_IT_TXE, DISABLE);

	/* enable usart */
	USART_Cmd(CONSOLE_USART, ENABLE);
}

void usart1_put_char(uint8_t c) {
	/* wait last transmission completed */
	while (USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_TXE) == RESET);

	/* put transmission data */
	USART_SendData(CONSOLE_USART, (uint8_t)c);

	/* wait transmission completed */
	while (USART_GetFlagStatus(CONSOLE_USART, USART_FLAG_TC) == RESET);
}

void usart2_init() {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* enable clocks */
	RCC_AHBPeriphClockCmd(ESP8266_LINK_GPIO_CLOCK, ENABLE);
	RCC_APB1PeriphClockCmd(ESP8266_LINK_USART_CLOCK, ENABLE);

	/* pin af config */
	GPIO_PinAFConfig(ESP8266_LINK_GPIO_PORT, ESP8266_LINK_TX_PIN_SOURCE, ESP8266_LINK_GPIO_AF);
	GPIO_PinAFConfig(ESP8266_LINK_GPIO_PORT, ESP8266_LINK_RX_PIN_SOURCE, ESP8266_LINK_GPIO_AF);

	/* gpio config */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = ESP8266_LINK_TX_PIN;
	GPIO_Init(ESP8266_LINK_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ESP8266_LINK_RX_PIN;
	GPIO_Init(ESP8266_LINK_GPIO_PORT, &GPIO_InitStructure);

	/* usart1 config */
	USART_InitStructure.USART_BaudRate = ESP8266_LINK_USART_SPEED;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(ESP8266_LINK_USART, &USART_InitStructure);

	/* enable the usart interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = ESP8266_LINK_INTERRUPT;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_ClearITPendingBit(ESP8266_LINK_USART, USART_IT_RXNE | USART_IT_TXE);
	USART_ITConfig(ESP8266_LINK_USART, USART_IT_RXNE, ENABLE);
	USART_ITConfig(ESP8266_LINK_USART, USART_IT_TXE, DISABLE);

	/* enable usart */
	USART_Cmd(ESP8266_LINK_USART, ENABLE);
}

void usart2_put_char(uint8_t c) {
	/* wait last transmission completed */
	while (USART_GetFlagStatus(ESP8266_LINK_USART, USART_FLAG_TXE) == RESET);

	/* put transmission data */
	USART_SendData(ESP8266_LINK_USART, (uint8_t)c);

	/* wait transmission completed */
	while (USART_GetFlagStatus(ESP8266_LINK_USART, USART_FLAG_TC) == RESET);
}

void pwm_init() {
	/* enable clocks */
	RCC_APB1PeriphClockCmd(L298_TIMER_CLOCK_SOURCE, ENABLE);
	RCC_AHBPeriphClockCmd(L298_GPIO_CLOCK_SOURCE, ENABLE);

	/* gpio config */
	L298_GPIOInitStructure.GPIO_Pin = L298_GPIO_PIN;
	L298_GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF;
	L298_GPIOInitStructure.GPIO_OType = GPIO_OType_PP;
	L298_GPIOInitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	L298_GPIOInitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(L298_GPIO_PORT, &L298_GPIOInitStructure);
	GPIO_PinAFConfig(L298_GPIO_PORT, L298_GPIO_PIN_SOURCE, GPIO_AF_TIM3);

	/* timer config */
	uint16_t prescaler = (uint16_t)(SystemCoreClock / 8000000) - 1;
	L298_TimerInitStructure.TIM_Period = 1332;
	L298_TimerInitStructure.TIM_Prescaler = prescaler;
	L298_TimerInitStructure.TIM_ClockDivision = 0;
	L298_TimerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(L298_TIMER, &L298_TimerInitStructure);

	/* pwm config */
	L298_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	L298_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	L298_OCInitStructure.TIM_Pulse = 0;
	L298_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC3Init(L298_TIMER, &L298_OCInitStructure);
	TIM_OC3PreloadConfig(L298_TIMER, TIM_OCPreload_Enable);

	/* enable timer */
	TIM_ARRPreloadConfig(L298_TIMER, ENABLE);
	TIM_Cmd(L298_TIMER, ENABLE);
}

void pwm_set_duty_cycle(uint32_t ccr_set) {
    TIM_SetCompare3(L298_TIMER, ccr_set);
}

void l298n_dir_init() {
	GPIO_InitTypeDef        GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(L298_DIR_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = L298_IN1_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(L298_DIR_IO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = L298_IN2_IO_PIN;
	GPIO_Init(L298_DIR_IO_PORT, &GPIO_InitStructure);

	/* default state */
	GPIO_SetBits(L298_DIR_IO_PORT, L298_IN1_IO_PIN);
	GPIO_ResetBits(L298_DIR_IO_PORT, L298_IN2_IO_PIN);
}

void spi1_init() {
	GPIO_InitTypeDef  GPIO_InitStructure;
	SPI_InitTypeDef   SPI_InitStructure;
	
	/* enable clocks */
	RCC_AHBPeriphClockCmd(ST7789_IO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(ST7789_SPI_CLOCK, ENABLE);

	/* gpio config */
	GPIO_InitStructure.GPIO_Pin = ST7789_SCK_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_Init(ST7789_IO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = ST7789_SDA_IO_PIN;
	GPIO_Init(ST7789_IO_PORT, &GPIO_InitStructure);

	/* pin af config */
	GPIO_PinAFConfig(ST7789_IO_PORT, ST7789_SCK_IO_PIN_SOURCE, GPIO_AF_SPI1);
	GPIO_PinAFConfig(ST7789_IO_PORT, ST7789_SDA_IO_PIN_SOURCE, GPIO_AF_SPI1);

	/* spi config */
	SPI_DeInit(ST7789_SPI);
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_Init(ST7789_SPI, &SPI_InitStructure);
	
	/* enable spi after init */
	SPI_Cmd(ST7789_SPI, ENABLE);
}

void spi1_send_data(uint8_t data) {
	/* wait until transmit completed */
	while (SPI_I2S_GetFlagStatus(ST7789_SPI, SPI_I2S_FLAG_TXE) == RESET);

	/* transmit data */
	SPI_I2S_SendData(ST7789_SPI, (uint8_t)data);
}

/* dma structure for spi */
DMA_InitTypeDef DMA_TX_InitStructure;
void dma_init() {
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	DMA_TX_InitStructure.DMA_BufferSize = 170 * 320; //default
	DMA_TX_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
	DMA_TX_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_TX_InitStructure.DMA_MemoryBaseAddr = 0;
	DMA_TX_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_TX_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_TX_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_TX_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(ST7789_SPI->DR));
	DMA_TX_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_TX_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_TX_InitStructure.DMA_Priority = DMA_Priority_High;
}

void spi_send_dma(uint8_t* buffer_send, uint32_t length) {
	DMA_DeInit(DMA1_Channel3);

	DMA_TX_InitStructure.DMA_BufferSize = length;
	DMA_TX_InitStructure.DMA_MemoryBaseAddr = (uint32_t)buffer_send;
	DMA_Init(DMA1_Channel3, &DMA_TX_InitStructure);

	/* enable SPI Rx/Tx DMA request*/
	DMA_Cmd(DMA1_Channel3, ENABLE);
	SPI_I2S_DMACmd(ST7789_SPI, SPI_I2S_DMAReq_Tx, ENABLE);

	/* waiting for the end of data transfer */
	while(!(DMA_GetFlagStatus(DMA1_FLAG_TC3)));

	/* clear flag */
	DMA_ClearFlag(DMA1_FLAG_TC3);

	/* disable tranfers */
	DMA_Cmd(DMA1_Channel3, DISABLE);
	SPI_I2S_DMACmd(ST7789_SPI, SPI_I2S_DMAReq_Tx, DISABLE);
}

void st7789_dc_pin_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(ST7789_DC_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = ST7789_DC_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(ST7789_DC_IO_PORT, &GPIO_InitStructure);
}

void st7789_cs_pin_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(ST7789_CS_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = ST7789_CS_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(ST7789_CS_IO_PORT, &GPIO_InitStructure);
}

void st7789_rst_pin_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(ST7789_RST_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = ST7789_RST_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(ST7789_RST_IO_PORT, &GPIO_InitStructure);
}

void st7789_cs_write_pin_high() {
	GPIO_SetBits(ST7789_CS_IO_PORT, ST7789_CS_IO_PIN);
}

void st7789_cs_write_pin_low() {
	GPIO_ResetBits(ST7789_CS_IO_PORT, ST7789_CS_IO_PIN);
}

void st7789_dc_write_pin_high() {
	GPIO_SetBits(ST7789_DC_IO_PORT, ST7789_DC_IO_PIN);
}

void st7789_dc_write_pin_low() {
	GPIO_ResetBits(ST7789_DC_IO_PORT, ST7789_DC_IO_PIN);
}

void st7789_rst_write_pin_high() {
	GPIO_SetBits(ST7789_RST_IO_PORT, ST7789_RST_IO_PIN);
}

void st7789_rst_write_pin_low() {
	GPIO_ResetBits(ST7789_RST_IO_PORT, ST7789_RST_IO_PIN);
}

void encoder_exti_a_init() {
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* enable clock */
	RCC_AHBPeriphClockCmd(ENCODER_PINA_IO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* gpio config */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = ENCODER_PINA_IO_PIN;
	GPIO_Init(ENCODER_PINA_IO_PORT, &GPIO_InitStructure);
	
	/* connect EXTI3 Line to PB3 pin */
	SYSCFG_EXTILineConfig(ENCODER_PINA_PORT_SOURCE, ENCODER_PINA_PIN_SOURCE);

	/* exti config */
	EXTI_InitStructure.EXTI_Line = ENCODER_PINA_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* enable and set EXTI3 interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_PINA_IRQ_CHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void encoder_exti_b_init() {
	GPIO_InitTypeDef  GPIO_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	/* enable clock */
	RCC_AHBPeriphClockCmd(ENCODER_PINB_IO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	/* gpio config */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Pin = ENCODER_PINB_IO_PIN;
	GPIO_Init(ENCODER_PINB_IO_PORT, &GPIO_InitStructure);
	
	/* connect EXTI3 Line to PB3 pin */
	SYSCFG_EXTILineConfig(ENCODER_PINB_PORT_SOURCE, ENCODER_PINB_PIN_SOURCE);

	/* exti config */
	EXTI_InitStructure.EXTI_Line = ENCODER_PINB_EXTI_LINE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;  
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);

	/* enable and set EXTI3 interrupt to the lowest priority */
	NVIC_InitStructure.NVIC_IRQChannel = ENCODER_PINB_IRQ_CHANNEL;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void encoder_io_init() {
	encoder_exti_a_init();
	encoder_exti_b_init();
}

void i2c_init() {
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* enable clocks */
	RCC_APB1PeriphClockCmd(INA219_I2C_CLOCK_SOURCE, ENABLE);
	RCC_AHBPeriphClockCmd(INA219_GPIO_CLOCK, ENABLE);
	RCC_APB2PeriphClockCmd(INA219_SYSCFG_CLOCK, ENABLE);

	/* reset I2C peripheral */
	RCC_APB1PeriphResetCmd(INA219_I2C_CLOCK_SOURCE, ENABLE);
	/* release reset signal of I2C IP */
	RCC_APB1PeriphResetCmd(INA219_I2C_CLOCK_SOURCE, DISABLE);

	/* gpio pin af config */
	GPIO_PinAFConfig(INA219_GPIO_PORT, INA219_SDA_PIN_AF, INA219_GPIO_AF);
	GPIO_PinAFConfig(INA219_GPIO_PORT, INA219_SCL_PIN_AF, INA219_GPIO_AF);

	/* gpio config */
	GPIO_InitStructure.GPIO_Pin = INA219_SCL_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(INA219_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = INA219_SDA_PIN;
	GPIO_Init(INA219_GPIO_PORT, &GPIO_InitStructure);

	/* i2c config */
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_16_9;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;

	/* i2c enable */
	I2C_Cmd(INA219_I2C, ENABLE);
	I2C_Init(INA219_I2C, &I2C_InitStructure);
}

int i2c_write(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length) {
    /* wait until I2C is not busy */
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    /* generate START condition */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* wait for EV5 (start condition generated) */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    /* send device address for write */
    I2C_Send7bitAddress(I2C1, device_addr, I2C_Direction_Transmitter);

    /* wait for EV6 - address acknowledged */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    /* send register address */
    I2C_SendData(I2C1, reg_addr);

	/* wait for EV8_2 - register address transfer finished */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* send data bytes */
    for (int i = 0; i < length; i++) {
        I2C_SendData(I2C1, data[i]);
        /* Wait for EV8_2 - data byte transfer finished */
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
    }

    /* generate STOP condition */
    I2C_GenerateSTOP(I2C1, ENABLE);

    return 0;
}

int i2c_read(uint8_t device_addr, uint8_t reg_addr, uint8_t *data, int length) {
    /* wait until I2C is not busy */
    while (I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));

    /* generate START condition */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* wait for EV5 - start condition generated */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    /* send device address for write */
    I2C_Send7bitAddress(I2C1, device_addr, I2C_Direction_Transmitter);

	/* wait for EV6 - address acknowledged */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

    /* send register address */
    I2C_SendData(I2C1, reg_addr);

    /* wait for EV8_2 - register address transfer finished */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

    /* generate START condition again - repeated start */
    I2C_GenerateSTART(I2C1, ENABLE);

    /* wait for EV5 - start condition generated */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));

    /* send device address for read */
    I2C_Send7bitAddress(I2C1, device_addr, I2C_Direction_Receiver);

    /* wait for EV6 - address acknowledged */
    while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

    /* read data bytes */
    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            /* disable Acknowledgement for the last byte */
            I2C_AcknowledgeConfig(I2C1, DISABLE);
        }

        /* wait for EV7 (data received) */
        while (!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

        /* read data from I2C data register */
        data[i] = I2C_ReceiveData(I2C1);
    }

    /* generate STOP condition */
    I2C_GenerateSTOP(I2C1, ENABLE);

    /* re-enable Acknowledgement for next reception */
    I2C_AcknowledgeConfig(I2C1, ENABLE);

    return 0;
}

void button_up_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_UP_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_UP_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_UP_IO_PORT, &GPIO_InitStructure);
}

void button_down_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_DOWN_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_DOWN_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_DOWN_IO_PORT, &GPIO_InitStructure);
}

void button_mode_init() {
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHBPeriphClockCmd(BUTTON_MODE_IO_CLOCK, ENABLE);

	GPIO_InitStructure.GPIO_Pin   = BUTTON_MODE_IO_PIN;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(BUTTON_MODE_IO_PORT, &GPIO_InitStructure);
}

uint8_t button_up_read() {
	return (GPIO_ReadInputDataBit(BUTTON_UP_IO_PORT, BUTTON_UP_IO_PIN));
}

uint8_t button_down_read() {
	return (GPIO_ReadInputDataBit(BUTTON_DOWN_IO_PORT, BUTTON_DOWN_IO_PIN));
}

uint8_t button_mode_read() {
	return (GPIO_ReadInputDataBit(BUTTON_MODE_IO_PORT, BUTTON_MODE_IO_PIN));
}

void usart3_init() {
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;

	/* enable clocks */
	RCC_AHBPeriphClockCmd(DFPLAYER_GPIO_CLOCK, ENABLE);
	RCC_APB1PeriphClockCmd(DFPLAYER_USART_CLOCK, ENABLE);

	/* pin af config */
	GPIO_PinAFConfig(DFPLAYER_GPIO_PORT, DFPLAYER_TX_PIN_SOURCE, DFPLAYER_GPIO_AF);
	GPIO_PinAFConfig(DFPLAYER_GPIO_PORT, DFPLAYER_RX_PIN_SOURCE, DFPLAYER_GPIO_AF);

	/* gpio config */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = DFPLAYER_TX_PIN;
	GPIO_Init(DFPLAYER_GPIO_PORT, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = DFPLAYER_RX_PIN;
	GPIO_Init(DFPLAYER_GPIO_PORT, &GPIO_InitStructure);

	/* usart1 config */
	USART_InitStructure.USART_BaudRate = DFPLAYER_USART_SPEED;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(DFPLAYER_USART, &USART_InitStructure);

	USART_ITConfig(DFPLAYER_USART, USART_IT_TXE, DISABLE);

	/* enable usart */
	USART_Cmd(DFPLAYER_USART, ENABLE);
}

void usart3_put_char(uint8_t c) {
	/* wait last transmission completed */
	while (USART_GetFlagStatus(DFPLAYER_USART, USART_FLAG_TXE) == RESET);

	/* put transmission data */
	USART_SendData(DFPLAYER_USART, (uint8_t)c);

	/* wait transmission completed */
	while (USART_GetFlagStatus(DFPLAYER_USART, USART_FLAG_TC) == RESET);
}

void usart3_put_chars(uint8_t* str, uint16_t len) {
    for (uint16_t i = 0; i < len; i++) {
        usart3_put_char(str[i]);
    }
}

void io_init() {
	/* pwm init */
	pwm_init();

	/* l298n init */
	l298n_dir_init();

	/* encoder io init */
	encoder_io_init();

	/* spi init */
	spi1_init();
	dma_init();

	/* usart2 init */
	usart2_init();

	/* usart3 init */
	usart3_init();

	/* i2c init */
	i2c_init();

	/* st7789 io pin init */
	st7789_cs_pin_init();
	st7789_dc_pin_init();
	st7789_rst_pin_init();
	st7789_cs_write_pin_high();

	/* led life init */
	led_life_init();

	/* button init */
	button_up_init();
	button_down_init();
	button_mode_init();
}

