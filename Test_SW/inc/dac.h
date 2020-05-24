#ifndef __DAC_H__
#define __DAC_H__

#include <stdint.h>
#include "hw_base.h"

#define DAC_CR1 _SFR_(0x380)
#define DAC_CR1_EN             1u << 0
#define DAC_CR1_BOFF           1u << 0
#define DAC_CR1_TEN            1u << 0
#define DAC_CR1_TSEL_TIM4_TRIG 0u << 3
#define DAC_CR1_TSEL_SWTRIG    7u << 3

#define DAC_RDHRH _SFR_(0x388)

#define DAC_RDHRL _SFR_(0x389)

void init_dac(void);

void set_dac(uint16_t milivolts);

#endif
