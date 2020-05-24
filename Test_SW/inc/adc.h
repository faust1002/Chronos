#ifndef __ADC_H__
#define __ADC_H__

#include <stdint.h>
#include "hw_base.h"

#define ADC1_CR1 _SFR_(0x340)
#define ADC1_CR1_ADON   1u << 0
#define ADC1_CR1_START  1u << 1
#define ADC1_CR1_CONT   1u << 2
#define ADC1_CR1_EOCIE  1u << 3
#define ADC1_CR1_AWDIE  1u << 4
#define ADC1_CR1_RES_12 0u << 5
#define ADC1_CR1_RES_10 1u << 5
#define ADC1_CR1_RES_8  2u << 5
#define ADC1_CR1_RES_6  3u << 5
#define ADC1_CR1_OVERIE 1u << 7

#define ADC1_CR3 _SFR_(0x342)
#define ADC1_CR3_CHSEL0        0u << 0
#define ADC1_CR3_CHSEL1        1u << 0
#define ADC1_CR3_CHSEL2        2u << 0
#define ADC1_CR3_CHSEL3        3u << 0
#define ADC1_CR3_CHSEL4        4u << 0
#define ADC1_CR3_CHSEL5        5u << 0
#define ADC1_CR3_CHSEL6        6u << 0
#define ADC1_CR3_CHSEL7        7u << 0
#define ADC1_CR3_CHSEL8        8u << 0
#define ADC1_CR3_CHSEL9        9u << 0
#define ADC1_CR3_CHSEL10       10u << 0
#define ADC1_CR3_CHSEL11       11u << 0
#define ADC1_CR3_CHSEL12       12u << 0
#define ADC1_CR3_CHSEL13       13u << 0
#define ADC1_CR3_CHSEL14       14u << 0
#define ADC1_CR3_CHSEL15       15u << 0
#define ADC1_CR3_CHSEL16       16u << 0
#define ADC1_CR3_CHSEL17       17u << 0
#define ADC1_CR3_CHSEL18       18u << 0
#define ADC1_CR3_CHSEL19       19u << 0
#define ADC1_CR3_CHSEL20       20u << 0
#define ADC1_CR3_CHSEL21       21u << 0
#define ADC1_CR3_CHSEL22       22u << 0
#define ADC1_CR3_CHSEL23       23u << 0
#define ADC1_CR3_CHSEL24       24u << 0
#define ADC1_CR3_CHSEL25       25u << 0
#define ADC1_CR3_CHSEL26       26u << 0
#define ADC1_CR3_CHSEL27       27u << 0
#define ADC1_CR3_CHSEL_VREFINT 28u << 0
#define ADC1_CR3_CHSEL_TS      29u << 0
#define ADC1_CR3_SMTP2_4   0u << 5
#define ADC1_CR3_SMTP2_9   1u << 5
#define ADC1_CR3_SMTP2_16  2u << 5
#define ADC1_CR3_SMTP2_24  3u << 5
#define ADC1_CR3_SMTP2_48  4u << 5
#define ADC1_CR3_SMTP2_96  5u << 5
#define ADC1_CR3_SMTP2_192 6u << 5
#define ADC1_CR3_SMTP2_384 7u << 5

#define ADC1_SR _SFR_(0x343)
#define ADC1_SR_EOC  1u << 0
#define ADC1_SR_AWD  1u << 1
#define ADC1_SR_OVER 1u << 2

#define ADC1_DRH _SFR_(0x344)

#define ADC1_DRL _SFR_(0x345)

#define ADC1_TRIG1 _SFR_(0x34E)
#define ADC1_TRIG1_TRIG24    1u << 0
#define ADC1_TRIG1_TRIG25    1u << 1
#define ADC1_TRIG1_TRIG26    1u << 2
#define ADC1_TRIG1_TRIG27    1u << 3
#define ADC1_TRIG1_VREFINTON 1u << 4
#define ADC1_TRIG1_TSON      1u << 5

typedef enum
{
    adc0 = ADC1_CR3_CHSEL2,
    adc1 = ADC1_CR3_CHSEL1
} adc1_index_t;

uint16_t adc1_read_internal_voltage_reference(void);

uint16_t adc1_read(adc1_index_t index);

#endif
