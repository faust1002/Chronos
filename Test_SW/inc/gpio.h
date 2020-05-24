#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include "hw_base.h"

#define PC_ODR _SFR_(0x0A)
#define PC_ODR0 1u << 0
#define PC_ODR1 1u << 1
#define PC_ODR2 1u << 2
#define PC_ODR3 1u << 3
#define PC_ODR4 1u << 4
#define PC_ODR5 1u << 5
#define PC_ODR6 1u << 6
#define PC_ODR7 1u << 7

#define PC_IDR _SFR_(0x0B)
#define PC_IDR0 1u << 0
#define PC_IDR1 1u << 1
#define PC_IDR2 1u << 2
#define PC_IDR3 1u << 3
#define PC_IDR4 1u << 4
#define PC_IDR5 1u << 5
#define PC_IDR6 1u << 6
#define PC_IDR7 1u << 7

#define PC_DDR _SFR_(0x0C)
#define PC_DDR0 1u << 0
#define PC_DDR1 1u << 1
#define PC_DDR2 1u << 2
#define PC_DDR3 1u << 3
#define PC_DDR4 1u << 4
#define PC_DDR5 1u << 5
#define PC_DDR6 1u << 6
#define PC_DDR7 1u << 7

#define PC_CR1 _SFR_(0x0D)
#define PC_CR10 1u << 0
#define PC_CR11 1u << 1
#define PC_CR12 1u << 2
#define PC_CR13 1u << 3
#define PC_CR14 1u << 4
#define PC_CR15 1u << 5
#define PC_CR16 1u << 6
#define PC_CR17 1u << 7

#define PD_ODR _SFR_(0x0F)
#define PD_ODR0 1u << 0
#define PD_ODR1 1u << 1
#define PD_ODR2 1u << 2
#define PD_ODR3 1u << 3
#define PD_ODR4 1u << 4
#define PD_ODR5 1u << 5
#define PD_ODR6 1u << 6
#define PD_ODR7 1u << 7

#define PD_IDR _SFR_(0x10)
#define PD_IDR0 1u << 0
#define PD_IDR1 1u << 1
#define PD_IDR2 1u << 2
#define PD_IDR3 1u << 3
#define PD_IDR4 1u << 4
#define PD_IDR5 1u << 5
#define PD_IDR6 1u << 6
#define PD_IDR7 1u << 7

#define PD_DDR _SFR_(0x11)
#define PD_DDR0 1u << 0
#define PD_DDR1 1u << 1
#define PD_DDR2 1u << 2
#define PD_DDR3 1u << 3
#define PD_DDR4 1u << 4
#define PD_DDR5 1u << 5
#define PD_DDR6 1u << 6
#define PD_DDR7 1u << 7

#define PD_CR1 _SFR_(0x12)
#define PD_CR10 1u << 0
#define PD_CR11 1u << 1
#define PD_CR12 1u << 2
#define PD_CR13 1u << 3
#define PD_CR14 1u << 4
#define PD_CR15 1u << 5
#define PD_CR16 1u << 6
#define PD_CR17 1u << 7

void init_gpio(void);

typedef enum
{
    off = 0,
    on  = 1
} led_state_t;

typedef enum
{
    first_led      = PC_ODR1,
    second_led     = PC_ODR2
} led_index_t;

void set_led_state(led_index_t, led_state_t);
void toggle_led_state(led_index_t);

typedef enum
{
    first_btn      = PD_IDR5,
#if __REV_X302__
    second_btn     = PD_IDR1,
#else
    second_btn     = PD_IDR4,
#endif
    number_of_btns = 2
} btn_index_t;

uint8_t read_btn_state(btn_index_t);

#endif
