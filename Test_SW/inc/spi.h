#ifndef __SPI_H__
#define __SPI_H__

#include <stdint.h>
#include "hw_base.h"

#define SPI1_CR1 _SFR_(0x200)
#define SPI1_CR1_CPHA     1u << 0
#define SPI1_CR1_CPOL     1u << 1
#define SPI1_CR1_MSTR     1u << 2
#define SPI1_CR1_BR_2     0u << 3
#define SPI1_CR1_BR_4     1u << 3
#define SPI1_CR1_BR_8     2u << 3
#define SPI1_CR1_BR_16    3u << 3
#define SPI1_CR1_BR_32    4u << 3
#define SPI1_CR1_BR_64    5u << 3
#define SPI1_CR1_BR_128   6u << 3
#define SPI1_CR1_BR_256   7u << 3
#define SPI1_CR1_SPE      1u << 6
#define SPI1_CR1_LSBFIRTS 1u << 7

#define SPI1_CR2 _SFR_(0x201)
#define SPI1_CR2_SSI     1u << 0
#define SPI1_CR2_SSM     1u << 1
#define SPI1_CR2_RXONLY  1u << 2
#define SPI1_CR2_CRCNEXT 1u << 4
#define SPI1_CR2_CRCEN   1u << 5
#define SPI1_CR2_BDOE    1u << 6
#define SPI1_CR2_BDM     1u << 7

#define SPI1_SR _SFR_(0x203)
#define SPI1_SR_RXNE   1u << 0
#define SPI1_SR_TXE    1u << 1
#define SPI1_SR_WKUP   1u << 3
#define SPI1_SR_CRCERR 1u << 4
#define SPI1_SR_MODF   1u << 5
#define SPI1_SR_OVR    1u << 6
#define SPI1_SR_BSY    1u << 7

#define SPI1_DR _SFR_(0x204)

void init_spi1(void);

void spi1_write(uint8_t* buffer, uint8_t length);

#endif
