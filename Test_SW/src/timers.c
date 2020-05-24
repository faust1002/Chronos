#include <stdint.h>
#include <stdio.h>
#include "clock.h"
#include "interrupts.h"
#include "timers.h"

static isr_t tim4_isr_ptr = NULL;

void init_tim4(uint8_t tim_freq)
{
    const uint32_t divider = (1 << TIM4_PSCR_15) * tim_freq;
    const uint32_t sys_clock_frequency = get_clock_frequency();
    const uint32_t arr = sys_clock_frequency / divider;

    TIM4_PSCR = TIM4_PSCR_15;
    TIM4_ARR  = arr;

    TIM4_IER = TIM4_IER_UIE;
    TIM4_CR1 = TIM4_CR1_CEN;
}

void set_tim4_isr(isr_t ptr)
{
    tim4_isr_ptr = ptr;
}

void tim4_isr(void) __interrupt(TIM4_IRQ_NO)
{
    tim4_isr_ptr();

    TIM4_SR &= ~TIM4_SR_TIF;
}
