#ifndef __IWDG_H__
#define __IWDG_H__

#include <stdint.h>
#include "hw_base.h"

#define IWDG_KR _SFR_(0xE0)
#define KEY_ENABLE 0xCC
#define KEY_REFRESH 0xAA
#define KEY_ACCESS 0x55

#define IWDG_PR _SFR_(0xE1)
#define IWDG_PR_4   0u << 0
#define IWDG_PR_8   1u << 0
#define IWDG_PR_16  2u << 0
#define IWDG_PR_32  3u << 0
#define IWDG_PR_64  4u << 0
#define IWDG_PR_128 5u << 0
#define IWDG_PR_256 6u << 0

void init_iwdg(void);

void reset_iwdg(void);

#endif
