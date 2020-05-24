#include <stdio.h>
#include "clock.h"
#include "usart.h"

static isr_t usart1_rx_isr_ptr = NULL;

void init_usart1(uint16_t usart_baudrate)
{
    const uint32_t sys_clock_frequency = get_clock_frequency();
    const uint16_t divider = (sys_clock_frequency + usart_baudrate - 1) / usart_baudrate;

    USART1_BRR1 = (divider >> 4) & 0xFFu;
    USART1_BRR2 = divider & 0xFu | divider >> 8;

    USART1_CR3 = USART1_CR3_STOP_1;
    USART1_CR2 = USART1_CR2_REN | USART1_CR2_TEN | USART1_CR2_RIEN;
}

void set_usart1_rx_isr(isr_t ptr)
{
    usart1_rx_isr_ptr = ptr;
}

void usart1_rx_isr(void) __interrupt(USART1_RX_IRQ_NO)
{
    usart1_rx_isr_ptr();
}

char usart1_read_character()
{
    return USART1_DR;
}

void usart1_write_character(char c)
{
    USART1_DR = c;
    while (!(USART1_DR & USART1_SR_TC));
}

static void usart1_write_newline(void)
{
    usart1_write_character('\r');
    usart1_write_character('\n');
}

void usart1_write_line(const char* line)
{
    while (line != NULL)
    {
        usart1_write_character(*line);
        ++line;
    }
    usart1_write_newline();
}

static void usart1_write_integer(uint8_t value)
{
    while (value > 10)
    {
        uint8_t character = value % 10 + 0x30;
        usart1_write_character(character);
        value /= 10;
    }
}

void usart1_write_uint8_t(uint8_t value)
{
    usart1_write_integer(value);
    usart1_write_newline();
}

void usart1_write_uint16_t(uint16_t value)
{
    usart1_write_integer(value & 0xFF);
    usart1_write_integer(value >> 8);
    usart1_write_newline();
}
