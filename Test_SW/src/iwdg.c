#include "iwdg.h"

void init_iwdg(void)
{
    IWDG_KR = KEY_ENABLE;
    IWDG_KR = KEY_ACCESS;
    IWDG_PR = IWDG_PR_256;

    reset_iwdg();
}

void reset_iwdg(void)
{
    IWDG_KR = KEY_REFRESH;
}
