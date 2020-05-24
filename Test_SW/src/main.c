#include "adc.h"
#include "clock.h"
#include "dac.h"
#include "gpio.h"
#include "interrupts.h"
#include "iwdg.h"
#include "nop.h"
#include "spi.h"
#include "syscfg.h"
#include "timers.h"
#include "usart.h"
#include "mcp41010.h"

static uint8_t led_cnt                 = 0;
static uint8_t adc1_cnt                = 0;
static uint8_t btn_cnt[number_of_btns] = {0, 0};

static uint8_t led_flag   = 0;
static uint8_t btn_flag   = 0;
static uint8_t adc1_flag  = 0;

void tim4_irq(void)
{
    ++led_cnt;
    const uint8_t led_threshold = 250;
    if (led_cnt >= led_threshold)
    {
        led_cnt  = 0;
        led_flag = 1;
    }

    ++adc1_cnt;
    const uint8_t adc1_threshold = 42;
    if (adc1_cnt >= adc1_threshold)
    {
        adc1_cnt  = 0;
        adc1_flag = 1;
    }

    for (uint8_t btn_idx = 0; btn_idx != number_of_btns; ++btn_idx)
    {
        if (read_btn_state(btn_idx))
        {
            ++btn_cnt[btn_idx];
        }
        else
        {
            btn_cnt[btn_idx] = 0;
        }

        const uint8_t btn_threshold = 127;
        if (btn_cnt[btn_idx] >= btn_threshold)
        {
            btn_cnt[btn_idx] = 0;
            btn_flag         = 1;
        }
    }
}

void usart1_rx_irq(void)
{
    char c = usart1_read_character();
    usart1_write_character(c);
}

void init(void)
{
    init_default_clock_settings();

    init_iwdg();

    enable_interrupts();

    init_gpio();
    set_led_state(first_led, on);
    set_led_state(second_led, off);

    const uint8_t tim4_freq = 255;
    init_tim4(tim4_freq);
    set_tim4_isr(tim4_irq);

    const uint16_t usart_baudrate = 9600;
    init_usart1(usart_baudrate);
    set_usart1_rx_isr(usart1_rx_irq);

    usart1_write_line("Welcome to Chronos test SW!");

    usart1_write_line("Internal reference voltage");
    uint16_t voltage = adc1_read_internal_voltage_reference();
    usart1_write_uint16_t(voltage);

    init_dac();
    const uint16_t dac_voltage = 1650;
    set_dac(dac_voltage);

    init_spi1();
}

int main(void)
{
    init();

    while (1)
    {
        if (led_flag)
        {
            toggle_led_state(first_led);
            toggle_led_state(second_led);
            usart1_write_line("Blink");
            led_flag = 0;
        }

        if (adc1_flag)
        {
            uint16_t voltage_adc0 = adc1_read(adc0);
            usart1_write_line("Voltage (ADC0))");
            usart1_write_uint16_t(voltage_adc0);
            uint16_t voltage_adc1 = adc1_read(adc1);
            usart1_write_line("Voltage (ADC1))");
            usart1_write_uint16_t(voltage_adc1);
            adc1_flag = 0;
        }

        if (btn_flag)
        {
            usart1_write_line("Button pressed");
            btn_flag = 0;
        }

        reset_iwdg();
        nop();
    }
}
