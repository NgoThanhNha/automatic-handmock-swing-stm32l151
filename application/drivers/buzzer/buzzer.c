/**
 ******************************************************************************
 * @author: Nark
 * @date:   17/05/2024
 ******************************************************************************
**/

#include "buzzer.h"

#include "stm32l1xx_rcc.h"
#include "stm32l1xx_gpio.h"
#include "stm32l1xx_tim.h"
#include "misc.h"

#include "hard_timer.h"

volatile       uint32_t          _beep_duration;
volatile       bool              _tones_playing;
volatile const tone_t*			 _tones;

GPIO_InitTypeDef GPIO_InitStructure;

void buzzer_irq( void ) {
	if (BUZZER_TIM->SR & TIM_SR_UIF) {
		BUZZER_TIM->SR &= ~TIM_SR_UIF; // Clear the TIMx's interrupt pending bit

		_beep_duration--;
		if (_beep_duration == 0) {
			if (_tones_playing) {
				/* currently playing tones, take next tone */
				_tones++;
				if (_tones->frequency == 0 && _tones->duration == 0) {
					/* last tone in sequence */
					buzzer_disable();
					_tones_playing = false;
					_tones = NULL;
				} else {
					if (_tones->frequency == 0) {
						/* silence period */
						BUZZER_TIM->ARR = SystemCoreClock / (100 * BUZZER_TIM->PSC) - 1;
						BUZZER_TIM->CCR3 = 0; // 0% duty cycle
						_beep_duration = _tones->duration + 1;
					} else {
						/* play next tone in sequence */
						buzzer_enable(_tones->frequency,_tones->duration);
					}
				}
			} 
			else {
				buzzer_disable();
			}
		}
	}
}

void buzzer_init() {
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	NVIC_InitTypeDef NVIC_InitStruct;

	RCC_AHBPeriphClockCmd(BUZZER_IO_CLOCK, ENABLE);
	RCC_APB1PeriphClockCmd(BUZZER_TIM_PERIPH, ENABLE);

	GPIO_InitStructure.GPIO_Pin = BUZZER_IO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_40MHz;
	GPIO_Init(BUZZER_IO_PORT, &GPIO_InitStructure);
	GPIO_PinAFConfig(BUZZER_IO_PORT, BUZZER_IO_SOURCE, BUZZER_IO_AF);
	GPIO_ResetBits(BUZZER_IO_PORT, BUZZER_IO_PIN);

	TIM_DeInit(BUZZER_TIM);
	TIM_TimeBaseStructure.TIM_Prescaler = SystemCoreClock / 4000000;
	TIM_TimeBaseStructure.TIM_Period = 999;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(BUZZER_TIM, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_Pulse = 499;

	TIM_OC1Init(BUZZER_TIM, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(BUZZER_TIM, TIM_OCPreload_Enable);

	NVIC_InitStruct.NVIC_IRQChannel = BUZZER_TIM_IRQ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_Init(&NVIC_InitStruct);

	TIM_ARRPreloadConfig(BUZZER_TIM, ENABLE);
	TIM_ITConfig(BUZZER_TIM, TIM_IT_Update, ENABLE);

	/* BUZZER TIM enable counter */
	TIM_Cmd(BUZZER_TIM, ENABLE);

	/* BUZZER disable */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(BUZZER_IO_PORT, &GPIO_InitStructure);
	delay_ms(1);
}

/*
turn on buzzer with specified frequency
	input: freq - PWM frequency for buzzer (Hz)
	duration - duration of buzzer work (tens ms: 1 -> 10ms sound duration) 
*/
void buzzer_enable(uint16_t freq, uint32_t duration) {
	if (freq < 100 || freq > 8000 || duration == 0) {
		buzzer_disable();
	} else {
		_beep_duration = (freq / 100) * duration + 1;

		/* configure buzzer pin */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_Init(BUZZER_IO_PORT, &GPIO_InitStructure);

		/* configure and enable PWM timer */
		RCC->APB1ENR |= BUZZER_TIM_PERIPH; /* enable TIMx peripheral */
		BUZZER_TIM->ARR = SystemCoreClock / (freq * BUZZER_TIM->PSC) - 1;
		BUZZER_TIM->CCR3 = BUZZER_TIM->ARR >> 1; /* 50% duty cycle */
		BUZZER_TIM->CR1 |= TIM_CR1_CEN; /* counter enable */
	}
}

void buzzer_disable() {
	/* counter disable */
	BUZZER_TIM->CR1 &= ~TIM_CR1_CEN;
	/* disable TIMx peripheral to conserve power */
	RCC->APB1ENR &= ~BUZZER_TIM_PERIPH;
	/* configure buzzer pin as analog input without pullup to conserve power */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(BUZZER_IO_PORT, &GPIO_InitStructure);
}

/*
start playing tones sequence
	input: tones - pointer to tones array
*/
void buzzer_play_tone(const tone_t * tones) {
	_tones = tones;
	_tones_playing = true;
	buzzer_enable(_tones->frequency,_tones->duration);
}
