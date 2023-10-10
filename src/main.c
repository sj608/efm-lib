#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"

volatile uint32_t msTicks = 0;

void Delay(uint32_t dlyTicks);

int main (void)
{
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);

    if(SysTick_Config(SystemCoreClock / 1000)){
        while(1);
    }

    GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);

    while(1){
        GPIO_PinOutClear(gpioPortC, 0);
        Delay(100);
        GPIO_PinOutSet(gpioPortC, 0);
        Delay(100);
    }

}

void SysTick_Handler(void)
{
    msTicks++;
}

void Delay(uint32_t dlyTicks)
{
    uint32_t curTicks;
    curTicks = msTicks;
    while((msTicks - curTicks) < dlyTicks);
}

