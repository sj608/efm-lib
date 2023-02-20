#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "serial.h"
#include "flash.h"

extern int dummy_int;

volatile uint32_t msTicks = 0;
volatile char rx_char = 0;

void Delay(uint32_t dlyTicks);
int dummy_for_loop(int a, int b);

int main (void)
{
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_USART2, true);

    if(SysTick_Config(SystemCoreClock / 1000)){
        while(1);
    }

    serial_init();
    GPIO_PinModeSet(gpioPortC, 0, gpioModePushPull, 0);

    while(1){

        dummy_int = dummy_for_loop(0, 10);

        GPIO_PinOutClear(gpioPortC, 0);
        Delay(500);
        GPIO_PinOutSet(gpioPortC, 0);
        Delay(500);
        // serial_main(rx_char);
    }

}

void SysTick_Handler(void)
{
    msTicks++;
}

void Delay(uint32_t dlyTicks)
{
    uint32_t curTicks;
    uint32_t ticks = 0;
    curTicks = msTicks;
    while((msTicks - curTicks) < dlyTicks)
    {
        ticks++;
    }
}

void USART2_RX_IRQHandler(void)
{
    USART_IntClear(usart, USART_IF_RXDATAV);
    rx_char = USART_Rx(usart);
} 

int dummy_for_loop(int a, int b)
{
    static int c = 0;
    for (int i = a; i < b; i++)
    {
        c+=i;
    }
    return c;
}