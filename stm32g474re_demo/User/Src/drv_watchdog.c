

#include "drv_watchdog.h"
#include "main.h"






void hal_watchdog_feed(void)
{
    LL_IWDG_ReloadCounter(IWDG);
}
