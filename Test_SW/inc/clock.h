#ifndef __CLOCK_HW__
#define __CLOCK_HW__

#include <stdint.h>
#include "hw_base.h"

#define CLK_DIVR  _SFR_(0xC0)
#define CKM_DIVIDER_0   0x0
#define CKM_DIVIDER_2   0x1
#define CKM_DIVIDER_4   0x2
#define CKM_DIVIDER_8   0x3
#define CKM_DIVIDER_16  0x4
#define CKM_DIVIDER_32  0x5
#define CKM_DIVIDER_64  0x6
#define CKM_DIVIDER_128 0x7

#define CLK_ICKCR _SFR_(0xC2)
#define ICKCR_HSION     1u << 0
#define ICKCR_HSIRDY    1u << 1
#define ICKCR_LSION     1u << 2
#define ICKCR_LSIRDY    1u << 3
#define ICKCR_SAHALT    1u << 4
#define ICKCR_FHWU      1u << 5
#define ICKCR_BEEPAHALT 1u << 6

#define CLK_PCKENR1 _SFR_(0xC3)
#define PCKEN10_TIM2   1u << 0
#define PCKEN11_TIM3   1u << 1
#define PCKEN12_TIM4   1u << 2
#define PCKEN13_I2C1   1u << 3
#define PCKEN14_SPI1   1u << 4
#define PCKEN15_USART1 1u << 5
#define PCKEN16_BEEP   1u << 6
#define PCKEN17_DAC    1u << 7

#define CLK_PCKENR2 _SFR_(0xC4)
#define PCKEN20_ADC1 1u << 0
#define PCKEN21_TIM1 1u << 1
#define PCKEN22_RTC  1u << 2
#define PCKEN23_LCD  1u << 3
#define PCKEN24_DMA1 1u << 4
#define PCKEN25_COMP 1u << 5
#define PCKEN27_ROM  1u << 7

void init_default_clock_settings(void);
uint32_t get_clock_frequency(void);

#endif
