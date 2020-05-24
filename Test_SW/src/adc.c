#include "vref.h"
#include "adc.h"


uint16_t calculate_voltage(uint8_t low, uint8_t high)
{
    const uint8_t adc1_resolution = ADC1_CR1_RES_12;
    uint8_t number_of_bits = 12 - 2 * (adc1_resolution >> 5);
    uint16_t voltage = (VREF >> number_of_bits) * (high << 8 | low);
    return voltage;
}

uint16_t adc1_read_internal_voltage_reference(void)
{
    ADC1_CR3 = ADC1_CR3_CHSEL_VREFINT;
    ADC1_CR1 = ADC1_CR1_ADON;

    ADC1_TRIG1 |= ADC1_TRIG1_VREFINTON;
    ADC1_CR1 |= ADC1_CR1_START;
    while (!(ADC1_SR && ADC1_SR_EOC));

    uint8_t low  = ADC1_DRL;
    uint8_t high = ADC1_DRH;

    ADC1_SR &= ~ADC1_SR_EOC;
    ADC1_TRIG1 &= ~ADC1_TRIG1_VREFINTON;
    ADC1_CR1 &= ~ADC1_CR1_ADON;

    return calculate_voltage(low, high);
}

uint16_t adc1_read(adc1_index_t index)
{
    ADC1_CR3 = index;
    ADC1_CR1 = ADC1_CR1_ADON;

    ADC1_CR1 |= ADC1_CR1_START;
    while (!(ADC1_SR && ADC1_SR_EOC));

    uint8_t low  = ADC1_DRL;
    uint8_t high = ADC1_DRH;

    ADC1_SR &= ~ADC1_SR_EOC;
    ADC1_CR1 &= ~ADC1_CR1_ADON;

    return calculate_voltage(low, high);
}
