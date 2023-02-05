
#include "led.h"
#include "main.h"









void led_task(void)
{
    LL_GPIO_TogglePin(GPIOA, LL_GPIO_PIN_5);
}