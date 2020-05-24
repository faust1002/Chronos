#include "clock.h"

static uint8_t clk_divider = CKM_DIVIDER_8;

void init_default_clock_settings(void)
{
    CLK_DIVR    = CKM_DIVIDER_0;
    CLK_PCKENR1 = PCKEN14_SPI1 | PCKEN12_TIM4 | PCKEN15_USART1 | PCKEN17_DAC;
    CLK_PCKENR2 = PCKEN20_ADC1;

    clk_divider = CKM_DIVIDER_0;

    CLK_ICKCR |= ICKCR_LSION;
    while (!(CLK_ICKCR & ICKCR_LSIRDY));
}

uint32_t get_clock_frequency(void)
{
    const uint32_t max_clk_freq = 16000000;
    return (max_clk_freq >> clk_divider);
}
