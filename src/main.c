#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_i2c.h"

volatile uint32_t msTicks = 0;

void Delay(uint32_t dlyTicks);
void init_i2c(void);

int main (void)
{
    CMU_ClockEnable(cmuClock_HFPER, true);
    CMU_ClockEnable(cmuClock_GPIO, true);
    CMU_ClockEnable(cmuClock_I2C0, true);

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

void init_i2c(void)
{
    // Using default settings
    I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;
    // Use ~400khz SCK
    i2cInit.freq = I2C_FREQ_FAST_MAX;

    //TODO: This must be changed according to device
    GPIO_PinModeSet(gpioPortD, 6, gpioModeWiredAndPullUpFilter, 1);
    GPIO_PinModeSet(gpioPortD, 7, gpioModeWiredAndPullUpFilter, 1);

    //TODO: Enable pins at location 15 as specified in datasheet, this must be changed according to device
    I2C0->ROUTE = I2C_ROUTE_SDAPEN | I2C_ROUTE_SCLPEN;
    I2C0->ROUTE = (I2C0->ROUTE & (~_I2C_ROUTE_LOCATION_MASK)) | I2C_ROUTE_LOCATION_LOC1;

    // Initializing the I2C
    I2C_Init(I2C0, &i2cInit);
}
