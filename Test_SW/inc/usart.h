#ifndef __USART1_H__
#define __USART1_H__

#include <stdint.h>
#include "hw_base.h"
#include "interrupts.h"

#define USART1_SR _SFR_(0x230)
#define USART1_SR_PE   1u << 0
#define USART1_SR_FE   1u << 1
#define USART1_SR_NF   1u << 2
#define USART1_SR_OR   1u << 3
#define USART1_SR_IDLE 1u << 4
#define USART1_SR_RXNE 1u << 5
#define USART1_SR_TC   1u << 6
#define USART1_SR_TXE  1u << 7

#define USART1_DR _SFR_(0x231)

#define USART1_BRR1 _SFR_(0x232)

#define USART1_BRR2 _SFR_(0x233)

#define USART1_CR1 _SFR_(0x234)
#define USART1_CR1_PIEN   1u << 0
#define USART1_CR1_PS     1u << 1
#define USART1_CR1_PCEN   1u << 2
#define USART1_CR1_WAKE   1u << 3
#define USART1_CR1_M      1u << 4
#define USART1_CR1_USART1D 1u << 5
#define USART1_CR1_T8     1u << 6
#define USART1_CR1_R8     1u << 7

#define USART1_CR2 _SFR_(0x235)
#define USART1_CR2_SBK   1u << 0
#define USART1_CR2_RWU   1u << 1
#define USART1_CR2_REN   1u << 2
#define USART1_CR2_TEN   1u << 3
#define USART1_CR2_ILIEN 1u << 4
#define USART1_CR2_RIEN  1u << 5
#define USART1_CR2_TCIEN 1u << 6
#define USART1_CR2_TIEN  1u << 7

#define USART1_CR3 _SFR_(0x236)
#define USART1_CR3_LBCL    1u << 0
#define USART1_CR3_CPHA    1u << 1
#define USART1_CR3_CPOL    1u << 2
#define USART1_CR3_CLKEN   1u << 3
#define USART1_CR3_STOP_1  0u << 4
#define USART1_CR3_STOP_2  2u << 4
#define USART1_CR3_STOP_15 3u << 4

#define USART1_RX_IRQ_NO 28

void init_usart1(uint16_t usart_baudrate);
void set_usart1_rx_isr(isr_t ptr);

char usart1_read_character();

void usart1_write_character(char c);
void usart1_write_line(const char* line);
void usart1_write_uint8_t(uint8_t value);
void usart1_write_uint16_t(uint16_t value);

#endif
