#include "spi.h"

void init_spi1(void)
{
    SPI1_CR1 = SPI1_CR1_BR_256;
    SPI1_CR2 = SPI1_CR2_SSI | SPI1_CR2_SSM;
}

static void spi1_write_byte(uint8_t byte)
{
    SPI1_DR = byte;
    while (!(SPI1_SR & SPI1_SR_TXE));
}

void spi1_write(uint8_t* buffer, uint8_t length)
{
    SPI1_CR1 |= SPI1_CR1_SPE;
    for (uint8_t idx = 0u; idx != length; ++idx)
    {
        spi1_write_byte(buffer[idx]);
    }
    while (!(SPI1_SR & SPI1_SR_BSY));
    SPI1_SR &= SPI1_CR1_SPE;
}
