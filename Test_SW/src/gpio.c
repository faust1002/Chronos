#include "gpio.h"

void init_gpio(void)
{
#if __REV_X302__
    PC_CR1 = PC_CR11 | PC_CR15;
#else
    PC_CR1 = PC_CR14 | PC_CR15;
#endif

    PD_DDR = PD_DDR0 | PD_DDR1;
    PD_CR1 = PD_CR10 | PD_CR11;
}

void set_led_state(led_index_t index, led_state_t state)
{
    if (state == on)
    {
        PC_ODR |= index;
    }
    else
    {
        PC_ODR &= ~index;
    }
}

void toggle_led_state(led_index_t index)
{
    PC_ODR ^= index;
}

uint8_t read_btn_state(btn_index_t index)
{
    return (PD_IDR & index > 0);
}
