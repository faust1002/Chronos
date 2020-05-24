#include "interrupts.h"

void enable_interrupts(void)
{
    __asm__("rim");
}
