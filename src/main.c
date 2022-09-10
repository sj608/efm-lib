#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"

volatile uint32_t msTicks = 0;
char target_string[] = "hello world\n";
const uint8_t str_size = sizeof(target_string) / sizeof(char);
USART_TypeDef *usart = USART2;

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

void serial_init();
void send_string(void);

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
        send_string();
        GPIO_PinOutClear(gpioPortC, 0);
        Delay(500);
        GPIO_PinOutSet(gpioPortC, 0);
        Delay(500);
    }

}

void serial_init()
{
    USART_InitAsync_TypeDef init_async = USART_INITASYNC_DEFAULT;

	// Prepare struct for initializing UART in asynchronous mode
	init_async.enable       = usartDisable;   // Don't enable UART upon intialization
	init_async.refFreq      = 0;              // Provide information on reference frequency. When set to 0, the reference frequency is
	init_async.oversampling = usartOVS16;     // Oversampling. Range is 4x, 6x, 8x or 16x, default is 16x
	init_async.databits     = usartDatabits8; // Number of data bits. Range is 4 to 10
	init_async.parity       = usartNoParity;  // Parity mode
	init_async.stopbits     = usartStopbits1; // Number of stop bits. Range is 0 to 2
    init_async.baudrate     = 115200;

    USART_InitAsync(usart, &init_async);

	// Prepare UART Rx and Tx interrupts
	// USART_IntClear(usart, _USART_IF_MASK);
	// USART_IntEnable(usart, USART_IF_RXDATAV);

	// NVIC_ClearPendingIRQ(USART1_RX_IRQn);
	// NVIC_ClearPendingIRQ(USART1_TX_IRQn);
	// NVIC_EnableIRQ(USART1_RX_IRQn);
	// NVIC_EnableIRQ(USART1_TX_IRQn);

	// NVIC_SetPriority(USART1_RX_IRQn, 0);
	// NVIC_SetPriority(USART1_TX_IRQn, 0);

    usart->ROUTE = USART_ROUTE_RXPEN | USART_ROUTE_TXPEN | _USART_ROUTE_LOCATION_LOC0;

    USART_Enable(usart, usartEnable);
}

void send_string(void)
{
    // for(uint8_t i = 0; i < str_size; i++)
    // {
    //     while(usart->STATUS & USART_STATUS_TXBL);
    //     usart->TXDATA = target_string[i];
    //     while(usart->STATUS & USART_STATUS_TXC);
    // }
    USART_Tx(usart, 'a');
}

// void USART2_TX_IRQHandler(void)
// {
//     if(usart->STATUS & USART_STATUS_TXBL)
//     {
        
//     }

// }

// void USART0_RX_IRQHandler(void)
// {

// }