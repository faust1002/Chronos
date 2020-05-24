#include "ri.h"
#include "vref.h"
#include "dac.h"

void init_dac(void)
{
    RI_IOSR3 |= RI_IOSR3_CH15E;
    DAC_CR1 = DAC_CR1_EN;
}

void set_dac(uint16_t milivolts)
{
    uint32_t reg_value = (milivolts >> 12) / VREF;
    DAC_RDHRH = (reg_value >> 8) & 0xFu;
    DAC_RDHRL = reg_value & 0xFFu;
}
