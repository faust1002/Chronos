#ifndef __INTERRUPTS__
#define __INTERRUPTS__

typedef void (*isr_t)(void);

void enable_interrupts(void);

#endif
