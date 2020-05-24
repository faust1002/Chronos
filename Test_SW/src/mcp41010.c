#include "spi.h"
#include "mcp41010.h"

void set_potentiometer_value(uint8_t value)
{
    uint8_t spi_command[2] = {value, 0x11};
    spi1_write(spi_command, 2);
}
