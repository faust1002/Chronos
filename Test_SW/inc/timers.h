#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdint.h>
#include "hw_base.h"
#include "interrupts.h"

#define TIM4_CR1 _SFR_(0x2E0)
#define TIM4_CR1_CEN  1u << 0
#define TIM4_CR1_UDIS 1u << 1
#define TIM4_CR1_URS  1u << 2
#define TIM4_CR1_APRE 1u << 7

#define TIM4_IER _SFR_(0x2E4)
#define TIM4_IER_UIE 1u << 0
#define TIM4_IER_TIE 1u << 6

#define TIM4_SR _SFR_(0x2E5)
#define TIM4_SR_UIF 1u << 0
#define TIM4_SR_TIF 1u << 6

#define TIM4_PSCR _SFR_(0x2E8)
#define TIM4_PSCR_0  0u
#define TIM4_PSCR_1  1u
#define TIM4_PSCR_2  2u
#define TIM4_PSCR_3  3u
#define TIM4_PSCR_4  4u
#define TIM4_PSCR_5  5u
#define TIM4_PSCR_6  6u
#define TIM4_PSCR_7  7u
#define TIM4_PSCR_8  8u
#define TIM4_PSCR_9  9u
#define TIM4_PSCR_10 10u
#define TIM4_PSCR_11 11u
#define TIM4_PSCR_12 12u
#define TIM4_PSCR_13 13u
#define TIM4_PSCR_14 14u
#define TIM4_PSCR_15 15u

#define TIM4_ARR _SFR_(0x2E9)

#define TIM4_IRQ_NO 25

void init_tim4(uint8_t tim_freq);
void set_tim4_isr(isr_t ptr);

#endif
