#ifndef __HW_BASE__
#define __HW_BASE__

#include <stdint.h>

#define _SFR_(mem_addr) (*(volatile uint8_t*)(0x5000 + (mem_addr)))

#endif
